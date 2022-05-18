create or replace function register
(name in varchar2 , password in varchar2)
return number
is
	aux number(20);
	aux1 number(20);
begin
	select count(userindex) into aux 
		from userstable where username=name;
	
	if aux>0 then
		return -1;
	end if;

	select count(userindex) into aux from userstable;
	if aux = 0 then
		aux:=1;
	else
		select max(userindex) into aux from userstable;
		aux:=aux+1;
	end if;
	insert into userstable(userindex,username) values (aux , name);
	insert into userpasswordtable(userindex,userpassword) values (aux , password);
	
	select count(sessionnumber) into aux1 from freesessionnumbertable;
	if aux1 > 0 then
		select min(sessionnumber) into aux1 from freesessionnumbertable;
		delete from freesessionnumbertable where sessionnumber=aux1;
	else
		select count(sessionnumber) into aux1 from sessionnumbertable;
		if aux1 = 0 then
			aux1:=1;
		else
			select max(sessionnumber) into aux1 from sessionnumbertable;
			aux1:=aux1+1;
		end if;
	end if;
	insert into sessionnumbertable(userindex , sessionnumber) values (aux , aux1);

	commit;	
	return aux1;

end;
/

