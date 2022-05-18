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

        $edge['gid']=pg_fetch_result($query,0,0);
        $edge['source']=pg_fetch_result($query,0,1);
        $edge['target']=pg_fetch_result($query,0,2);
        $edge['the_geom']=pg_fetch_result($query,0,3);

        pg_close($con);

        return $edge;
    }

    function sql_query($start_edge,$end_edge){
        switch($_GET['method']){
            case 'SPD': 
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
            break;
            case 'SPA': 
                $sql="select rt.gid,ST_AsGeoJSON(rt.the_geom) as geojson,
                                length(rt.the_geom) as length,".TABLE.".gid
                        from ".TABLE.",
                            (select gid,the_geom
                                from astar_sp_delta(
                                        '".TABLE."',
                                        ".$start_edge['source'].",
                                        ".$end_edge['target'].",
                                        0.1)) as rt
                        where ".TABLE.".gid=rt.gid;";
            break;
            case 'SPS': // shootingstar(?_sp_delta?)
                $sql="select rt.gid,ST_AsGeoJSON(rt.the_geom) as geojson,
                                length(rt.the_geom) as length,".TABLE.".gid
                        from ".TABLE.",
                            (select gid,the_geom
                                from shootingstar_sp(  
                                        '".TABLE."',
                                        ".$start_edge['gid'].",
                                        ".$end_edge['gid'].",
                                        0.1,'length',true,true)) as rt
                        where ".TABLE.".gid=rt.gid;";
            break;
        }

        return $sql;
    }

    $start          =split(' ' , $_GET['startpoint']);
    $start_point    =array($start[0] , $start[1]);
    $end            =split(' ' , $_GET['finalpoint']);
    $end_point      =array($end[0] , $end[1]);

    error_log($start_point[0].$start_point[1]);
    error_log($end_point[0].$end_point[1]);

    $start_edge =find_nearest_edge($start_point);
    $end_edge   =find_nearest_edge($end_point);

    $dbcon=pg_connect("dbname=".PG_DB." host=".PG_HOST." user=".PG_USER." password=".PG_PASSWD);
    $sql=sql_query($start_edge,$end_edge);
    $query=pg_query($dbcon,$sql);

    $geojson=array(
        'type'      => 'FeatureCollection',
        'features'  => array());

    while($edge=pg_fetch_assoc($query)){
        //$str='';//--------------------------------
        //foreach($edge as $key => $val){//---------
        // $str=$str.' '.$key.' '.$val;}//----------
        //error_log($str);//------------------------
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
    pg_close($dbcon);

    header('Content-type: application/json',true);
    echo json_encode($geojson);

?>

