-- the coordinates for start and end point
-- 21.175113105985687 45.760905940327056 => 532
-- 21.26067759059322 45.73879251766385 => 2144 ;
-- gid = 615 needed ?!?
-- or reverse ?!? 2144 -> 532 though I dont think reversing is too important

-- query to determine the start/end points id's in the db
/*SELECT gid, source, target, the_geom, 
		          distance(the_geom, GeometryFromText(
		          'POINT(21.26067759059322 45.73879251766385)', 4326)) AS dist 
	             FROM ways  
	             WHERE the_geom && setsrid(
	                   'BOX3D(21.16067759059322
	                          45.63879251766385,
	                          21.36067759059322
	                          45.83879251766385)'::box3d, 4326) 
	             ORDER BY dist LIMIT 1;*/

-- call stack to explore
-- dijkstra_sp_delta
-- ->dijkstra_sp_delta_directed
-- ->shortest_path

-- dijkstra_sp_delta result for the id's of the start/end points
/*select rt.gid , ST_AsGeoJSON(rt.the_geom) as geojson ,
	length(rt.the_geom) as length , ways.gid
from ways ,
	(select gid , the_geom
	from dijkstra_sp_delta(
		'ways',532,2144,0.1)) as rt
	where ways.gid=rt.gid;*/

-- going into the call stack
/*select gid , the_geom
from dijkstra_sp_delta_directed(
	'ways',532,2144,0.1,false,false);*/

-- final function that has the c implementation
-- CREATE OR REPLACE FUNCTION shortest_path(sql text, source_id integer, target_id integer, directed boolean, has_reverse_cost boolean)
--  RETURNS SETOF path_result AS

-- query to find out srid
-- select srid(the_geom) from ways limit 1;

-- query to find out ll_x(y) and ur_x(y)
-- sourceid=532 / targetid=2144
-- source_x=21.1851068
-- source_y=45.7644262
-- target_x=21.258679
-- target_y=45.7395747
-- ll_x = min(source_x,target_x) = 21.1851068
-- ur_x = max(source_x,target_x) = 21.258679
-- ll_y = min(source_y,target_y) = 45.7395747
-- ur_y = max(source_y,target_y) = 45.7644262

/*select x(startpoint(the_geom)) as source_x 
from ways
where source=532 or target=532 -- where source=sourceid or target=sourceid
limit 1;*/

/*select y(startpoint(the_geom)) as source_y
from ways
where source=532 or target=532 -- where source=sourceid or target=sourceid
limit 1;*/

/*select x(startpoint(the_geom)) as target_x
from ways
where source=2144 or target=2144 -- where source=targetid or target=targetid
limit 1;*/

/*select y(startpoint(the_geom)) as target_y
from ways
where source=2144 or target=2144 -- where source=targetid or target=targetid
limit 1;*/

-- TODO what are srid , ll_x(y) and ur_x(y)
-- srid = 4326
-- ll_x =  
-- ll_y = 
-- ur_x = 
-- ur_y = 
-- delta = 0.1 by default chosen in the client

-- srid , ll_x(y) and ur_x(y) , delta not replaced
/*select gid , the_geom
from 	shortest_path(
		'select gid as id , source::integer , target::integer ,
			length::double precision as cost
		from ways where setSRID(''BOX3D(
			ll_x-delta , ll_y-delta , ur_x+delta ,
			ur_y+delta)''::BOX3D , srid) && the_geom' ,
			532 , 2144 , false , false) ,
	ways
where edge_id=gid;*/

-- srid , ll_x(y) , ur_x(y) , delta replaced
-- ll_x = min(source_x,target_x) = 21.1851068
-- ur_x = max(source_x,target_x) = 21.258679
-- ll_y = min(source_y,target_y) = 45.7395747
-- ur_y = max(source_y,target_y) = 45.7644262
/*select gid , the_geom
from 	shortest_path(
		'select gid as id , source::integer , target::integer ,
			length::double precision as cost
		from ways where setSRID(''BOX3D(
			21.0851068  45.6395747 , 21.358679 
			45.8644262)''::BOX3D , 4326) && the_geom' ,
			532 , 2144 , false , false) ,
	ways
where edge_id=gid;*/

/*select * from shortest_path(
		'select gid as id , source::integer , target::integer ,
			length::double precision as cost
		from ways where setSRID(''BOX3D(
			21.0851068  45.6395747 , 21.358679 
			45.8644262)''::BOX3D , 4326) && the_geom' ,
			532 , 2144 , false , false);*/

select column1 as x1,column2 as y1 from add_car_route_to_simulation(
	'ways',532,2144,0.1);

--select max(car_id) as the_max from car_paths;

/*select x1,y1,path_id
from ways,car_paths
where gid=edge_id and car_id=0
order by path_id;*/
