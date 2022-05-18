drop table userstable;
drop table userpasswordtable;
drop table sessionnumbertable;
drop table freesessionnumbertable;
drop table auction;
drop table auctiontimeinfo;
drop table auctionpriceinfo;
drop table bidtable;
drop table auctiondescription;
drop table itemtypelist;
drop table auctionstatusmeaning;
drop table dateformat;

exec clearjob();

drop table loopjobnumber;

drop function loginuser;
drop function register;
drop procedure expireauctions;
drop function setupauction;
drop function logoutuser;
drop procedure clearjob;
drop function makebid;
drop procedure getauctionlist;

drop package datatypes;

commit;

