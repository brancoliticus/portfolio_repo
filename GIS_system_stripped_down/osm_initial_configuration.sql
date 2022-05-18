--comment
--INSERT INTO spatial_ref_sys (srid, auth_name, auth_srid, srtext, proj4text)
--VALUES (900913, 'spatialreference.org', 900913,
--  'PROJCS["unnamed",GEOGCS["unnamed ellipse",DATUM["unknown",
--   SPHEROID["unnamed",6378137,0]],PRIMEM["Greenwich",0],
--   UNIT["degree",0.0174532925199433]],PROJECTION["Mercator_2SP"],
--   PARAMETER["standard_parallel_1",0],PARAMETER["central_meridian",0],
--   PARAMETER["false_easting",0],PARAMETER["false_northing",0],
--   UNIT["Meter",1],
--   EXTENSION["PROJ4","+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0
--   +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +wktext  +no_defs"]]',
--   '+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0
--   +k=1.0 +units=m +nadgrids=@null +wktext  +no_defs');
--
--present by default in postgis/postgres 8.4 in ubuntu 10.04
--
--
--
--
create user "www-data" with password 'www-data';
