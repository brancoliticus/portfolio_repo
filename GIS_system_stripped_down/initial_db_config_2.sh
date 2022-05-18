#!/bin/sh
createdb -E utf8 osm
createlang plpgsql osm
# see http://www.mail-archive.com/debian-bugs-dist@lists.debian.org/msg766170.html
# cat /usr/share/postgresql-8.3-postgis/lwpostgis.sql | psql -d osm
# cat /usr/share/postgresql-8.3-postgis/spatial_ref_sys.sql | psql -d osm
cat /usr/share/postgresql/8.4/contrib/postgis.sql | psql -d osm
cat /usr/share/postgresql/8.4/contrib/spatial_ref_sys.sql | psql -d osm
