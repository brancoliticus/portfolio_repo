createdb routing
psql -d routing -c "create procedural language plpgsql;"
createlang plpgsql routing
createuser routing

cat /usr/share/postgresql/8.4/contrib/postgis.sql 	  | psql -d routing
cat /usr/share/postgresql/8.4/contrib/spatial_ref_sys.sql | psql -d routing

cat /usr/share/postlbs/routing_core.sql 		| psql -d routing
cat /usr/share/postlbs/routing_core_wrappers.sql 	| psql -d routing
cat /usr/share/postlbs/routing_topology.sql 		| psql -d routing

osm2pgrouting -file "/home/ubuntu/Desktop/data_transfer_folder/timisoara.osm"\
	-conf "/usr/share/osm2pgrouting/mapconfig.xml"\
	-dbname routing -user postgres -passwd postgres -clean
