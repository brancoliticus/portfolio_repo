create or replace procedure delete_entry(
	entryname varchar2) as

	cf number(10);
	aux number(10);
	tf number(10);
	mf number(10);
begin
	select max(currentfolder) into cf from fsinfotable;
	
	select count(filename) into aux from filetable
		where filename=entryname and parentfolder=cf;
	if aux > 0 then
		delete from filetable 
			where filename=entryname and parentfolder=cf;
		print_line('file ' || entryname || ' deleted');
		return;
	end if;
	
	select count(foldernumber) into aux from foldertable
		where parentfolder=cf and foldername=entryname;
	if aux=0 then
		print_line('no entry with name ' || entryname);
		return;
	end if;
	
	select foldernumber into tf from foldertable
		where parentfolder=cf and foldername=entryname;
	
	update fsinfotable set currentfolder=tf where currentfolder=cf;
	
	for fentry in (select * from filetable where parentfolder=tf) loop
		delete_entry(fentry.filename);
	end loop;
	
	for fentry in (select * from foldertable where parentfolder=tf) loop
		delete_entry(fentry.foldername);
	end loop;
	
	delete from foldertable where foldernumber=tf;
	select max(foldernumber) into mf from foldertable;
	if mf < tf then -- delete fnumbers from freefolderstable greater than new maximum
		delete from freefolderstable where foldernumber > mf;
	else -- add the just deleted foldernumber to freefolderstable
		insert into freefolderstable(foldernumber) values(tf);
	end if;
	
	update fsinfotable set currentfolder=cf where currentfolder=tf;
	print_line('folder ' || entryname || ' deleted');
end;
/