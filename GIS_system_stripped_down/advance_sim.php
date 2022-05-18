<?php

    define("PG_DB"      , "routing");
    define("PG_HOST"    , "localhost");
    define("PG_USER"    , "routing");
    define("PG_PASSWD"  , "routing");
    define("PG_PORT"    , "5432");

    function advance_sim_query($timestep){
        return 
            "select advance_sim as sim_status ".
            "from advance_sim(".$timestep.");";}

    $timestep=$_GET['timestep'];
    $timestep=floatval($timestep);

    /*TODO call advance_sim plpgsql function with the timestep */
    $dbcon=pg_connect("dbname=".PG_DB." host=".PG_HOST.
            " user=".PG_USER." password=".PG_PASSWD);
        $sql=advance_sim_query($timestep);
        $query=pg_query($dbcon,$sql);
        $sim_status_container=pg_fetch_assoc($query);
        $sim_status=$sim_status_container['sim_status'];
    pg_close($dbcon);

    header('Content-type: application/json',true);
    echo json_encode($sim_status);

?>
