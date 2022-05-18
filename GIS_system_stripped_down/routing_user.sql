\c routing

create user routing with password 'routing';

grant select on table ways to routing;

grant select on table car_paths to routing;
grant insert on table car_paths to routing;
grant delete on table car_paths to routing;

grant select on table car_pos to routing;
grant insert on table car_pos to routing;
grant delete on table car_pos to routing;
grant update on table car_pos to routing;
