create or replace function setupauction
(usersessionnumber in number , itemtypenameparam in varchar2 ,
	minbidprice in number , itemdescription in varchar2 ,
	auctionduration in number)
return number
is
	auxuserindex number(20);
	auxitemtypeid number(20);
	auxauctionid number(20);
	auxdateformat varchar2(20);
	auxdate date;
--(auctionid in number(20))

	--dbms_job.submit(
   	--	what=>'expireauction.sql;',
   	--	next_date=>sysdate+1, -- start
   	--	interval=>'NULL');
begin
	if auctionduration <= 0 then
		return -1;
	end if;
	select userindex into auxuserindex from sessionnumbertable where sessionnumber=usersessionnumber;
	select itemtypeid into auxitemtypeid from itemtypelist where itemtypename=itemtypenameparam;
	select count(auctionid) into auxauctionid from auction;
	if auxauctionid=0 then
		auxauctionid:=1;
	else
		select max(auctionid) into auxauctionid from auction;
		auxauctionid:=auxauctionid+1;
	end if;
	insert into auction(auctionid,selleruserindex,itemtypeid,auctionstatus) values (auxauctionid,auxuserindex,auxitemtypeid,'a');

	insert into auctiontimeinfo(auctionid,startdate,durationminutes) values (auxauctionid,sysdate,auctionduration);
	insert into auctionpriceinfo(auctionid,minbid,currentmaxbid,maxbiduserindex) values(auxauctionid,minbidprice,-1,-1);
	insert into auctiondescription(auctionid,description) values(auxauctionid,itemdescription);

	commit;
	return auxauctionid;

exception
	when NO_DATA_FOUND then
		return -1;
end;
/
