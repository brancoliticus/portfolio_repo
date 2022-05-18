create table freefolderstable
(foldernumber number(10));

create table fsinfotable
(currentfolder number(10));

insert into fsinfotable(currentfolder) values (0);

create table foldertable
(foldernumber number(10),
foldername varchar2(20),
parentfolder number(10));

create table filetable
(filename varchar2(20),
content varchar2(200),
parentfolder number(10));

commit;

/
