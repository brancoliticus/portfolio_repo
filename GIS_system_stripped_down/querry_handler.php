<?php

header("Content-type: text/plain");

$dbconn=pg_connect("host=localhost dbname=osm " .
                    "user=www-data password=www-data")
            or error_log(pg_last_error());
$query=('select osm_id from osm_line fetch first 2 row only');
$db_result=pg_query($query) or error_log('query failed: ' . pg_last_error());
while($db_result_line=pg_fetch_array($db_result,null,PGSQL_ASSOC)){
    foreach($db_result_line as $rl){
        $result_line=$rl;
        error_log($result_line);
    }
}

$input=$_GET["input"];
$output="1 ->" . $input . " <- " . $result_line;
echo $output;

pg_free_result($db_result);
pg_close($dbconn);

?>
