create or replace procedure create_file(
	fname in varchar2 , fcontent in varchar2) as
	
	aux number(10);
	cf number(10);
	
begin
	if fname is null then
		print_line('please enter a filename and content');
		return;
	end if;
	if fcontent is null then
		print_line('please input content for ' || fname);
		return;
	end if;
	
	select max(currentfolder) into cf from fsinfotable;
	
	select count(foldernumber) into aux from foldertable
		where parentfolder=cf and foldername=fname;
	if aux > 0 then
		print_line('name alredy exists as folder name');
		return;
	end if;
	
	select count(filename)into aux from filetable
		where filename=fname and parentfolder=cf;
	if aux > 0 then
		print_line('file alredy exists');
		return;
	end if;
	
	insert into filetable(filename , content , parentfolder)
		values(fname , fcontent , cf);
	print_line('file ' || fname || ' created');
end;
/