create or replace function loginuser
(name in varchar2 , password in varchar2)
return number
is
	aux number(20);
	aux1 number(20);
begin
	
	select u.userindex into aux 
		from userstable u , userpasswordtable p
		where u.username=name and p.userpassword=password
		and u.userindex=p.userindex;

	select count(userindex) into aux1 from sessionnumbertable
		where userindex=aux;
	if aux1 > 0 then
		return -1;
	end if;

	select count(sessionnumber) into aux1 from freesessionnumbertable;
	if aux1 > 0 then
		select min(sessionnumber) into aux1 from freesessionnumbertable;
		delete from freesessionnumbertable where sessionnumber = aux1;
	else
		select count(sessionnumber) into aux1 from sessionnumbertable;
		if aux1=0 then
			aux1:=1;
		else
			select max(sessionnumber) into aux1 from sessionnumbertable;
			aux1:=aux1+1;
		end if;
	end if;
	insert into sessionnumbertable(userindex , sessionnumber) values (aux , aux1);
	commit;
	
	return aux1;

exception
	when NO_DATA_FOUND then
		return -1;	
	
end;
/
