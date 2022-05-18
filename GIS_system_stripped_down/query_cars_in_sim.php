<?php
    define("PG_DB","routing");
    define("PG_HOST","localhost");
    define("PG_USER","routing");
    define("PG_PASSWD","routing");
    define("PG_PORT","5432");

    function query_car_positions(){
        $sql=
            "select xpos , ypos ".
            " from car_pos";
        return $sql;
    }

    $dbcon=pg_connect("dbname=".PG_DB." host=".PG_HOST.
            " user=".PG_USER." password=".PG_PASSWD);
        $sql=query_car_positions();
        $query=pg_query($dbcon,$sql);
        $car_positions=array();
        while($car_pos=pg_fetch_assoc($query)){
            array_push($car_positions,$car_pos['xpos']);
            array_push($car_positions,$car_pos['ypos']);
        }
    pg_close($dbcon);

    header('Content-type: application/json',true);
    echo json_encode($car_positions);
?>
