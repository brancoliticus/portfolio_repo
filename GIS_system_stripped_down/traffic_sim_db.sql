\c routing

create or replace
-- input of dijkstra_sp_delta
function add_car_route_to_simulation(
    character varying , integer , integer , double precision ,
    out double precision , out double precision)
-- output of shortest_path that will be inserted to car_paths table
returns setof record as
$body$
declare
    -- input
    geom_table  alias for $1;
    sourceid    alias for $2;
    targetid    alias for $3;
    delta       alias for $4;
    x1          alias for $5;
    y1          alias for $6;
    --

    rec_aux     record;
    rec_aux1    record;
    counter     integer;
    final_query text;

    source_x float8;
    source_y float8;
    target_x float8;
    target_y float8;

    srid integer;
    ll_x float8;
    ll_y float8;
    ur_x float8;
    ur_y float8;

    the_car_id integer;
    
begin
    --body and auxiliary variables of dijkstra_sp_delta_directed

    for rec_aux in execute
        'select srid(the_geom) from ' ||
        quote_ident(geom_table) || ' limit 1'
    loop
    end loop;
    srid:=rec_aux.srid;

    for rec_aux in execute
        'select x(startpoint(the_geom)) as source_x from ' ||
        quote_ident(geom_table) || ' where source = ' ||
        sourceid || ' or target='||sourceid||' limit 1'
    loop
    end loop;
    source_x:=rec_aux.source_x;

    for rec_aux in execute
        'select y(startpoint(the_geom)) as source_y from ' ||
        quote_ident(geom_table) || ' where source = ' ||
        sourceid || ' or target='||sourceid||' limit 1'
    loop
    end loop;
    source_y:=rec_aux.source_y;

    for rec_aux in execute
        'select x(startpoint(the_geom)) as target_x from ' ||
        quote_ident(geom_table) || ' where source = ' ||
        targetid || ' or target='||targetid||' limit 1'
    loop
    end loop;
    target_x:=rec_aux.target_x;

    for rec_aux in execute
        'select y(startpoint(the_geom)) as target_y from ' ||
        quote_ident(geom_table) || ' where source = ' ||
        targetid || ' or target='||targetid||' limit 1'
    loop
    end loop;
    target_y:=rec_aux.target_y;

    for rec_aux in execute 'select case when '||source_x||'<'||target_x||
        ' then '||source_x||' else '||target_x||
        ' end as ll_x , case when '||source_x||'>'||target_x||
        ' then '||source_x||' else '||target_x||' end as ur_x'
    loop
    end loop;
    ll_x:=rec_aux.ll_x;
    ur_x:=rec_aux.ur_x;

    for rec_aux in execute 'select case when '||source_y||'<'||
        target_y||' then '||source_y||' else '||
        target_y||' end as ll_y,case when '||
        source_y||'>'||target_y||' then '||
        source_y||' else '||target_y||' end as ur_y'
    loop
    end loop;
    ll_y:=rec_aux.ll_y;
    ur_y:=rec_aux.ur_y;

    final_query:='select * from shortest_path('||
        '''select gid as id , source::integer , target::integer,'||
        'length::double precision as cost '||
        'from '||quote_ident(geom_table)||' where setSRID(''''BOX3D('||
        ll_x-delta||' '||ll_y-delta||','||ur_x+delta||' '||
        ur_y+delta||')''''::BOX3D, ' ||srid||') && the_geom'', '||
        quote_literal(sourceid) || ' , ' ||
        quote_literal(targetid) || ' , false , false);';

    for rec_aux in execute 'select count(car_id) as rowno from car_paths;'
    loop
    end loop;
    if rec_aux.rowno=0 then 
        the_car_id:=0;
    else
        for rec_aux in execute 'select max(car_id) as the_max from car_paths;'
        loop
        end loop;
        the_car_id:=rec_aux.the_max+1;
    end if;

    counter:=0;
    for rec_aux in execute final_query
    loop
        insert into 
        car_paths(car_id , edge_id , source_id ,
            path_id , length)
        values(the_car_id , rec_aux.edge_id , rec_aux.vertex_id ,
            counter , rec_aux.cost);

        if counter=0 then 
            for rec_aux1 in execute
                ' select x1,y1,x2,y2,source,target ' ||
                ' from ways ' ||
                ' where ' ||
                    ' gid= '    || rec_aux.edge_id || ' and ' ||
                    ' (source= ' || rec_aux.vertex_id || ' or ' ||
                    ' target= ' || rec_aux.vertex_id || ') '
            loop
                if rec_aux1.source=rec_aux.vertex_id then
                    x1:=rec_aux1.x1;
                    y1:=rec_aux1.y1;
                else
                    x1:=rec_aux1.x2;
                    y1:=rec_aux1.y2;
                end if;
            end loop;

            insert into -- initialise the car_pos table for current car 
            car_pos(car_id,path_id,position,xpos,ypos)
            values(the_car_id,0,0.0,x1,y1);
        end if;
        counter:=counter+1; -- 2 uses for counter

        for rec_aux1 in execute --return values unused for the moment
            'select x1,y1 '||
            'from ways '||
            'where gid='|| rec_aux.edge_id || ';'
        loop
            x1 := rec_aux1.x1;
            y1 := rec_aux1.y1;
            return next;
        end loop;
    end loop;

end;
$body$
    language 'plpgsql' volatile strict
    cost 100;

create or replace
function advance_sim(double precision)
returns varchar(1) as
$body$
declare
    timestep alias for $1;

    rec_carpos      record;
    rec_carpath     record;
    rec_aux         record;

    car_count integer;
    car_sim_exit integer;

    start_counting integer;
    finished_counting integer;

    covered_ground          double precision;
    ground_left_current_car double precision;

    x_pos double precision;
    y_pos double precision;

    car_position                double precision;

    the_edge_id         integer;
    the_source_vertex   integer;
    the_target_vertex   integer;

    bropen  integer;
    brclose integer;
    brspace integer;

    aux_textgeom text;
    aux_textgeom1 text;
begin

    car_count:=0;
    car_sim_exit:=0;
    covered_ground:=timestep*0.00833333333; -- 0.5/60=0.00833333333
    -- 1.0 in length column of car_paths table = 1km
    -- speed=30km/h=0.5km/min constant
    -- divide by 60 to get ground covered in 1sec
    for rec_carpos in
         select * from car_pos
    loop
        car_count:=car_count+1;
        ground_left_current_car:=covered_ground;
        start_counting:=0;
        car_position:=rec_carpos.position;
        
        for rec_carpath in
            select path_id , length , edge_id
            from car_paths
            where car_id=rec_carpos.car_id
            order by path_id asc
        loop
            if rec_carpath.edge_id=-1 then
                exit;   -- last row item displays the ending vertex of path
            end if;     -- with edge_id=-1 and isn't needed
            if start_counting=0 then
                if rec_carpath.path_id!=rec_carpos.path_id then
                    continue;
                else
                    start_counting:=1;
                end if;
            end if;
            
            ground_left_current_car:=ground_left_current_car -
                rec_carpath.length*(1.0-car_position);
            -- position is 1st time rec_carpos.position , then 0.0
            car_position:=0.0;
            
            if ground_left_current_car<0.0 then
                -- reuse car_position as going through this if exits loop
                car_position :=
                        ((rec_carpath.length+ground_left_current_car)
                        /rec_carpath.length);
                update car_pos
                set
                    position=car_position,
                    path_id=rec_carpath.path_id
                where car_id=rec_carpos.car_id;
                
                for rec_aux in
                    select  edge_id , source_id
                    from car_paths
                    where   car_id  =rec_carpos.car_id and 
                            path_id =rec_carpath.path_id
                loop
                    the_edge_id:=rec_aux.edge_id;
                    the_source_vertex:=rec_aux.source_id;
                end loop;
                
                the_target_vertex:=-1;
                for rec_aux in
                    select  target
                    from ways
                    where   source=the_source_vertex and
                            gid=the_edge_id
                loop    
                    the_target_vertex:=rec_aux.target;
                end loop;
                if the_target_vertex=-1 then
                    for rec_aux in
                        select source
                        from ways
                        where target=the_source_vertex and
                        gid=the_edge_id 
                    loop
                        the_target_vertex:=rec_aux.source;
                        car_position:=1.0-car_position; -- going in reverse
                    end loop; -- changes the number for the relative
                end if; --  position of the car
                
                select ST_AsText(ST_GeometryN(the_geom,1)) into aux_textgeom
                --GeometryN get linestring from the 1 member multilinestring
                from dijkstra_sp_delta('ways',the_source_vertex,the_target_vertex,0.1);
                -- use the_source_vertex and the_target_vertex through SELECT gid, AsText(the_geom) AS the_geom FROM dijkstra_sp_delta('ways', <the_source_vertex> 5700, <the_target_vertex> 6733, 0.1);
                
                select st_astext into aux_textgeom1
                from ST_AsText(ST_Line_Interpolate_Point(ST_GeomFromText(aux_textgeom),car_position));
                
                -- format of text to search in is Point(xpos ypos)
                bropen:=position('(' in aux_textgeom1);
                brspace:=position(' ' in aux_textgeom1);
                brclose:=position(')' in aux_textgeom1);
                select
                    cast(substring(
                        aux_textgeom1 from (bropen+1) for (brspace-bropen-1))
                    as double precision)
                into x_pos;
                select
                    cast(substring(
                        aux_textgeom1 from (brspace+1) for (brclose-brspace-1))
                    as double precision)
                into y_pos;
                
                update car_pos
                set 
                    xpos=x_pos,
                    ypos=y_pos
                where car_id=rec_carpos.car_id;
                -- the result should be one multilinestring to run through st_interpolate_line_string with car_position as the percentage position indicator
                -- result is xpos and ypos to update car_pos 
                exit; -- exit the car_paths loop , go to next car_pos
            end if;
        end loop;
        if ground_left_current_car>0.0 then -- car exited sim
            delete from car_pos
            where car_id=rec_carpos.car_id;
            
            car_sim_exit:=car_sim_exit+1;
        end if;
    end loop;
    
    if car_count=0 then
        return 'v'; --void=no simulation
    elsif car_count - car_sim_exit=0 then
        return 'e'; --exited=all cars exited sim at current advance_sim call
    else
        return 'k'; --ok=cars in sim , positions ready for querying
    end if;
    
end;
$body$
    language 'plpgsql' volatile strict
    cost 100;



create table car_paths(
    car_id integer,
    edge_id integer,
    source_id integer,
    -- source_id=start vertex on the next edge to go through
    -- the edge's id is the edge_id in the next table row
    -- at end of path the source_id is only the end vertex
        -- of current table row edge_id
    -- the table ways has only one edge for going both ways
        -- 1 way streets reverse length is 16*10^4 km for ok rooting results
    path_id integer,
    length double precision);
create index car_index1 on car_paths(car_id);
create index path_index on car_paths(path_id);

create table car_pos(
    car_id integer,
    path_id integer,
    position double precision, -- >0.0 start of edge <1.0 end of edge
    xpos double precision,
    ypos double precision);
create index car_index2 on car_pos(car_id);
