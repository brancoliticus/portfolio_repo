<?php

    define("PG_DB"      , "routing");
    define("PG_HOST"    , "localhost");
    define("PG_USER"    , "routing");
    define("PG_PASSWD"  , "routing");
    define("PG_PORT"    , "5432");
    define("TABLE"      , "ways");

    function find_nearest_edge($lonlat){
        $con=pg_connect("dbname=".PG_DB." host=".PG_HOST." user=".PG_USER." password=".PG_PASSWD);

        $sql="select gid,source,target,the_geom,
                    distance(the_geom,GeometryFromText(
                        'POINT(".$lonlat[0]." ".$lonlat[1].")',4326)) as dist
                from ".TABLE.
                " where the_geom && setsrid(
                    'BOX3D(".($lonlat[0]-0.1)." "
                            .($lonlat[1]-0.1)." , "
                            .($lonlat[0]+0.1)." "
                            .($lonlat[1]+0.1).")'::box3d,4326)
                order by dist limit 1";

        $query=pg_query($con,$sql);

        $edge['gid']        =pg_fetch_result($query,0,0);
        $edge['source']     =pg_fetch_result($query,0,1);
        $edge['target']     =pg_fetch_result($query,0,2);
        $edge['the_geom']   =pg_fetch_result($query,0,3);

        pg_close($con);

        return $edge;
    }

    function query_to_add_route($start_edge,$end_edge){
        return  "select column1 as x1 , column2 as y1 ".
                "from add_car_route_to_simulation(".
                    "'ways',".$start_edge['source'].",".
                    $end_edge['target'].",0.1);";
    }

    function query_to_disp_route($start_edge,$end_edge){
        $sql="select rt.gid,ST_AsGeoJSON(rt.the_geom) as geojson,
                            length(rt.the_geom) as length,".TABLE.".gid
                    from ".TABLE.",
                        (select gid,the_geom
                            from dijkstra_sp_delta(
                                    '".TABLE."',
                                    ".$start_edge['source'].",
                                    ".$end_edge['target'].",
                                    0.1)) as rt
                    where ".TABLE.".gid=rt.gid;";
        return $sql;
    }

    function query_for_new_car_id(){
        return "select max(car_id) as car_id from car_paths";
    }

    function query_for_xpos_ypos($car_id){
        return "select xpos,ypos from car_pos "
            ."where car_id=".$car_id;
    }

    $start=split(' ' , $_GET['startpoint']);
    $start_point=array($start[0] , $start[1]);
    $end=split(' ' , $_GET['finalpoint']);
    $end_point=array($end[0] , $end[1]);

    $start_edge=find_nearest_edge($start_point);
    $end_edge=find_nearest_edge($end_point);

    $dbcon=pg_connect("dbname=".PG_DB." host=".PG_HOST." user=".PG_USER." password=".PG_PASSWD);
        
        $sql=query_to_add_route($start_edge,$end_edge);
        $query=pg_query($dbcon,$sql);
        $path_to_output=array();
        while($path_point=pg_fetch_assoc($query)){
            array_push($path_to_output,$path_point['x1']);
            array_push($path_to_output,$path_point['y1']);
        }

        $sql=query_for_new_car_id();
        $query=pg_query($dbcon,$sql);
        $carid_container=pg_fetch_assoc($query);
        $car_id=$carid_container['car_id'];
        //$new_car_data=array(
            //'car_id'=>$car_id,
            //'car_path'=>$path_to_output);

        $sql=query_for_xpos_ypos($car_id);
        $query=pg_query($dbcon,$sql);
        $xpos_ypos_container=pg_fetch_assoc($query);
        $xpos=$xpos_ypos_container['xpos'];
        $ypos=$xpos_ypos_container['ypos'];
    
        $geojson=array(
            'type'      => 'FeatureCollection',
            'features'  => array());
        $sql=query_to_disp_route($start_edge,$end_edge);
        $query=pg_query($dbcon,$sql);
        while($edge=pg_fetch_assoc($query)){
            $feature=array(
                'type' => 'Feature',
                'geometry' => json_decode($edge['geojson'],true),
                'crs' => array(
                    'type' => 'EPSG',
                    'properties' => array('code' => '4326')),
                'properties' => array(
                    'id' => $edge['id'],
                    'length' => $edge['length']));
            array_push($geojson['features'],$feature);
        }
        $new_car_data=array(
            'car_id' => $car_id,
            'geojson' => $geojson,
            'xpos' => $xpos, 
            'ypos' => $ypos); /*TODO*/

    pg_close($dbcon);

    header('Content-type: application/json',true);
    echo json_encode($new_car_data);

?>
