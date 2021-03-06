create table userstable(
	userindex number(20),
	username varchar2(150)
);

create table userpasswordtable(
	userindex number(20),
	userpassword varchar2(50)
);

create table sessionnumbertable(
	userindex number(20),
	sessionnumber number(20)
);

create table freesessionnumbertable(
	sessionnumber number(20)
);

create table auction(
	auctionid number(20),
	selleruserindex number(20),
	itemtypeid number(20),
	auctionstatus char(1)
);

create table auctiontimeinfo(
	auctionid number(20),
	startdate date,
	durationminutes number(20)
);

create table auctionpriceinfo(
	auctionid number(20),
	minbid number(20),
	currentmaxbid number(20),
	maxbiduserindex number(20)
);

create table bidtable(
	auctionid number(20),
	userindex number(20),
	biddate date,
	bidvalue number(20)
);

create table auctiondescription(
	auctionid number(20),
	description varchar2(200)
);

create table itemtypelist(
	itemtypeid number(20),
	itemtypename varchar2(200)
);

insert into itemtypelist(itemtypeid , itemtypename) values(1,'art');
insert into itemtypelist(itemtypeid , itemtypename) values(2,'books');
insert into itemtypelist(itemtypeid , itemtypename) values(3,'clothes');
insert into itemtypelist(itemtypeid , itemtypename) values(4,'laptops');
insert into itemtypelist(itemtypeid , itemtypename) values(5,'stamps');

create table auctionstatusmeaning(
	statuschar char(1),
	meaning varchar2(50)
);

insert into auctionstatusmeaning values('a','active');
insert into auctionstatusmeaning values('w','won');
insert into auctionstatusmeaning values('f','finished');

create table dateformat(
	format varchar2(40)
);

insert into dateformat(format) values ('DD/MM/YYYY HH24:MI:SS');

create table loopjobnumber(
	jobnumber number(20)
);

variable jobnumber number;
exec dbms_job.submit(:jobnumber,what=>'expireauctions;',next_date=>sysdate+1/(24*60),interval=>'sysdate+1/(24*60)');
insert into loopjobnumber(jobnumber) values (:jobnumber);

commit;

-- select job,next_date,next_sec,failures,broken,SUBSTR(what,1,40) DESCRIPTION from user_jobs;
