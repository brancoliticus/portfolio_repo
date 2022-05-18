create or replace procedure parse_input(
	text_input in varchar2,
	command out varchar2,
	parameter out varchar2) as

	text_trimmed varchar2(220);
	space_location number(10);
	strsize number(10);

begin
	text_trimmed:=trim(text_input);
	strsize:=length(text_trimmed);
	if strsize=0 then
		command:='';
		parameter:='';
		return;
	end if;
	
	space_location:=instr(text_trimmed , ' ');
	if space_location=0 then
		if length(text_trimmed) > 20 then
			command:=substr(text_trimmed , 1 , 20);
		else
			command:=substr(text_trimmed , 1 , length(text_trimmed));
		end if;
		parameter:='';
		return;
	end if;

	if space_location > 20 then
		command:=substr(text_trimmed , 1 , 20);
	else
		command:=substr(text_trimmed , 1 , space_location);
	end if;
	command:=trim(command);
	
	parameter:=substr(text_trimmed , space_location , length(text_trimmed) - space_location + 1);
	parameter:=trim(parameter);
end;
/
