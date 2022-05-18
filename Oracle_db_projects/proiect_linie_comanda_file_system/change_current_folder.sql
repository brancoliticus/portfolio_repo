create or replace procedure change_current_folder(
	targetfoldername varchar2) as
	
	cf number(10);
	aux number(10);
	targetfoldernumber number(10);

begin
	if targetfoldername is null then
		print_line('please input a target folder name');
		return;
	end if;
	
	select max(currentfolder) into cf from fsinfotable;
	if targetfoldername = '..' then
		if cf = 0 then
			print_line('cannot go up ; alredy at root folder');
			return;
		end if;
		select parentfolder into aux from foldertable where foldernumber=cf;
		update fsinfotable set currentfolder=aux where currentfolder=cf;
		return;
	end if;
	select count(foldernumber) into aux from foldertable 
		where parentfolder=cf and foldername=targetfoldername;
	if aux = 0 then
		print_line('target folder doesn''t exist');
		return;
	end if;
	select foldernumber into targetfoldernumber from foldertable 
		where parentfolder=cf and foldername=targetfoldername;
	update fsinfotable set currentfolder=targetfoldernumber 
		where currentfolder=cf;
	print_line('folder changed to ' || targetfoldername);
end;
/
