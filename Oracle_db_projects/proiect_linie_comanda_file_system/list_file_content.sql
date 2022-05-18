create or replace procedure list_file_content(
	fname varchar2) as
	
	cf number(10);
	aux number(10);
	fcontent varchar2(200);
begin
	select max(currentfolder) into cf from fsinfotable;
	select count(filename) into aux from filetable
		where filename=fname and parentfolder=cf;
	if aux = 0 then
		print_line('file ' || fname || ' not found');
		return;
	end if;
	select content into fcontent from filetable
		where filename=fname and parentfolder=cf;
	print_line(fcontent);
	
end;
/