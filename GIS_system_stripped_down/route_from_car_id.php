<?php

    define("PG_DB","routing");
    define("PG_HOST","localhost");
    define("PG_USER","routing");
    define("PG_PASSWD","routing");
    define("PG_PORT","5432");

$car_id=$_GET['car_id'];
$pgcon=pg_connect("dbname=".PG_DB." host=".PG_HOST." user=".PG_USER." password=".PG_PASSWD);
$query_text="select x1,y1,path_id ".
    "from ways,car_paths ".
    //TEST
    "where gid=edge_id and car_id=0 ".
    //REAL CODE
    //"where gid=edge_id and car_id=".$car_id." ".
    "order by path_id;";
$raw_sql_path=pg_query($pgcon,$query_text);
    while($raw_path=pg_fetch_assoc($raw_sql_path)){
        array_push($coordinates_array,$raw_path['x1'],$raw_path['x2']);}
pg_close($pgcon);

//TEST
error_log(implode("," , $coordinates_array));

header('Content-type: application/json',true);
echo json_encode($coordinates_array);

?>
