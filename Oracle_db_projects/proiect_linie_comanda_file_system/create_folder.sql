create or replace procedure create_folder(
	fname varchar2) as
	
	aux number(10);
	pf number(10);
	cf number(10);
	fnumber number(10);
	
begin
	if fname is null then
		print_line('please give a folder name');
		return;
	end if;
	select max(currentfolder) into cf from fsinfotable;
	
	select count(foldernumber) into aux from foldertable
		where parentfolder=cf and foldername=fname;
	if aux > 0 then
		print_line('folder alredy exists');
		return;
	end if;
	
	select count(filename)into aux from filetable
		where filename=fname and parentfolder=cf;
	if aux > 0 then
		print_line('name alredy exists as file name');
		return;
	end if;
	
	select count(foldernumber) into aux from freefolderstable;
	if aux > 0 then
		select min(foldernumber) into fnumber from freefolderstable;
		delete from freefolderstable where foldernumber=fnumber;
	else
		select max(foldernumber) into fnumber from foldertable;
		if fnumber is null then
			fnumber:=1; -- root folder default 0
		else
			fnumber:=fnumber+1;
		end if;
	end if;
	
	insert into foldertable(foldernumber , foldername , parentfolder)
		values(fnumber , fname , cf);
	print_line('folder ' || fname || ' created');
end;
/