begin

--first test
--process_command('ls');

--test print_line function
--process_command('ls efjbedjf');

--test change directory up from root folder and error
--process_command('cd ..');
--process_command('cd jhefhf');

--test file/folder create/change/delete
process_command('ls'); --list empty space
process_command('mkdir'); --no folder name error
process_command('mkdir a'); -- create folder a
process_command('ls'); -- list folder a no files
process_command('del a'); -- delete folder a
process_command('ls'); -- list empty root folder
process_command('mkdir a'); -- recreate folder a
process_command('mkdir b'); -- create folder b
process_command('mf fa '); -- error no file content
process_command('mf fa ca'); -- create file fa content ca
process_command('mf fb cb djfhjdgfjgdf'); -- create file fb content cb ...
process_command('mf fc cc'); -- create file fc content fc
process_command('ls'); -- list 2 folders , 3 files
process_command('lf fa'); -- list content ca
process_command('lf fb'); -- list content cb ...
process_command('del fa'); -- delete file fa
process_command('ls'); -- list 2 folders , 2 files
process_command('mkdir a'); -- error folder alredy exists
process_command('mf fc kasbdfhgbf'); -- error file alredy exists
process_command('mf a had'); -- error folder a exists - don't create file
process_command('mkdir fb'); -- error file alredy exists - don't create folder
process_command('cd'); -- error no folder name
process_command('cd fa'); -- error no folder name fa
process_command('cd a'); -- change to empty folder
process_command('ls'); -- list empty folder
process_command('mkdir a'); -- create folder a
process_command('del a'); -- delete folder a
process_command('ls'); -- list empty space
process_command('cd ..'); --go up
process_command('ls'); -- list 2 folders , 2 files
process_command('cd a'); -- go to a
process_command('mkdir a'); -- create folder a
process_command('cd a'); -- go to a
process_command('mf fa cu');
process_command('mf fb cv');
process_command('lf fa');
process_command('lf fb'); -- list content for files fa and fb
process_command('ls'); -- list files fa , fb
process_command('cd ..'); -- go to /a
process_command('mkdir b');
process_command('cd b');
process_command('mf fa ce');
process_command('mf fb cf');
process_command('lf fa');
process_command('lf fb'); -- list content for /a/b/fa and fb
process_command('cd ..'); -- go to /a
process_command('cd ..'); -- go to /
process_command('del a'); -- delete all created structures in a and a
process_command('ls'); -- only 1 folder , 2 files

end;
/
