create or replace procedure list_current_folder_content as
	cf number(10);
	entrycount number(10);

begin
	select max(currentfolder) into cf from fsinfotable;
	
	entrycount:=0;
	print_line('folders');
	for fentry in (select * from foldertable where parentfolder=cf) loop
		print_line(fentry.foldername);
		entrycount:=entrycount+1;
	end loop;
	if entrycount=0 then
		print_line('no child folders found in current folder');
	else
		print_line(entrycount || 'folders found');
	end if;
	
	entrycount:=0;
	print_line('files');
	for fentry in (select * from filetable where parentfolder=cf) loop
		print_line(fentry.filename);
		entrycount:=entrycount+1;
	end loop;
	if entrycount=0 then
		print_line('no files found in current folder');
	else
		print_line(entrycount || 'files found');
	end if;
end;
/