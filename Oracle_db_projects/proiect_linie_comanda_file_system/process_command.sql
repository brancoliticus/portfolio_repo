create or replace procedure process_command(
	text_input in varchar2) as
	
	command varchar2(20);
	parameter varchar2(200);
	fname varchar2(20);
	fcontent varchar2(200);
	
begin
	--text:=:input_text_item;
	--:output_text_item:='tada';
	--command:=parse_input(:input_text_item , command , parameter);
	--parameter=get_parameter(:input_text_item);
	
	parse_input(text_input , command , parameter);
	if command = 'ls' then --print entryes in folder
		list_current_folder_content();
	elsif command = 'lf' then --print folder content
		list_file_content(parameter);
	elsif command = 'mkdir' then --create folder
		create_folder(parameter);
	elsif command = 'mf' then --create file : name content
		parse_input(parameter , fname , fcontent);
		create_file(fname , fcontent);
	elsif command = 'cd' then --change folder
		change_current_folder(parameter);
	elsif command = 'del' then --delete file or folder
		delete_entry(parameter);
	else
		print_line('command not recognised');
	end if;
end;
/

/*
- Se vor implementa comenzi pentru:
a. afisarea continutului/structurii folderului curent (fisiere/foldere fiu) ex: dir sau ls
b. afisarea continutului fiecarui fisier ex: lf <nume_fisier>
c. crearea unui folder in folderul actual ex: mkdir <nume_folder>
d. crearea unui fisier in folderul actual ex: mf <nume_fisier> "continut ..."
e. schimbarea folderului curent ex: cd .. sau cd nume_folder
f.  stergerea unui anumit fisier / folder (impreuna cu toate folderele si fisierele continute) ex: del <nume>
*/
