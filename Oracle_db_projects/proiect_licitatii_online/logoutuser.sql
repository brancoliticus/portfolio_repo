create or replace function logoutuser
(paramsessionnumber number)
return number 
is
	aux number(20);
	aux1 number(20);
begin
	select userindex into aux from sessionnumbertable 
		where sessionnumber=paramsessionnumber;
	delete from sessionnumbertable where userindex=aux;
	select max(sessionnumber) into aux1 from sessionnumbertable;
	if aux1 < paramsessionnumber then
		delete from freesessionnumbertable where sessionnumber > aux1;
	end if;
	commit;
	return paramsessionnumber;
exception
	when NO_DATA_FOUND then
		return -1;
end;
/
