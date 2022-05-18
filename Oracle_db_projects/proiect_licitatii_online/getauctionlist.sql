create or replace procedure getauctionlist
(usersessionnumberparam in number , auctionidparam in number , itemtypeparam in varchar2 , minpriceparam in number , maxpriceparam in number , listtypeparam in char , returncursor in out datatypes.auctionlistitemcursor)
--listtypeparam=
--'m' : user's auctions
--'w' : user's won auctions
--'a' : all active auctions
--'b' : all user's bids
is
	--returncursor datatypes.auctionlistitemcursor;
	auxuserindex number(20);
	auxmaxprice number(20);
	auxminprice number(20);
begin
	select userindex into auxuserindex from sessionnumbertable where sessionnumber=usersessionnumberparam;
	if auctionidparam != -1 then
		open returncursor for select a.auctionid,y.itemtypename,d.description,p.minbid,p.currentmaxbid,a.auctionstatus from auction a,itemtypelist y,auctiondescription d , auctionpriceinfo p where a.auctionid=auctionidparam and a.itemtypeid = y.itemtypeid and d.auctionid=a.auctionid and p.auctionid=a.auctionid;
		return;
	end if;
	if maxpriceparam=-1 then
		select count(p.currentmaxbid) into auxmaxprice from auctionpriceinfo p , auction a where a.auctionid=p.auctionid and (((listtypeparam='a' or listtypeparam='b') and a.auctionstatus='a') or (listtypeparam='m') or (listtypeparam='w' and a.auctionstatus='w'));
		if auxmaxprice != 0 then
			select max(p.currentmaxbid) into auxmaxprice from auctionpriceinfo p , auction a where a.auctionid=p.auctionid and (((listtypeparam='a' or listtypeparam='b') and a.auctionstatus='a') or (listtypeparam='m') or (listtypeparam='w' and a.auctionstatus='w'));
			if auxmaxprice = -1 then
				select max(p.minbid) into auxmaxprice from auctionpriceinfo p , auction a where a.auctionid=p.auctionid and (((listtypeparam='a' or listtypeparam='b') and a.auctionstatus='a') or (listtypeparam='m') or (listtypeparam='w' and a.auctionstatus='w'));
			end if;
		end if;
	else
		auxmaxprice:=maxpriceparam;
	end if;
	if minpriceparam=-1 then
		auxminprice:=0;
	else
		auxminprice:=minpriceparam;
	end if;
	if auxminprice > auxmaxprice or auxminprice < 0 or auxmaxprice < 0 then
		returncursor:=null;
		return;
	end if;
	if listtypeparam='a' then
		open returncursor for select a.auctionid , y.itemtypename , d.description , p.minbid , p.currentmaxbid , a.auctionstatus from auction a , itemtypelist y , auctiondescription d , auctionpriceinfo p where a.auctionstatus='a' and a.itemtypeid=y.itemtypeid and a.auctionid=d.auctionid and a.auctionid=p.auctionid and ((p.currentmaxbid=-1 and p.minbid>=auxminprice and p.minbid<=auxmaxprice) or (p.currentmaxbid>=auxminprice and p.currentmaxbid <= auxmaxprice)) and (trim(itemtypeparam) is null or y.itemtypename=itemtypeparam);
		return;
	elsif listtypeparam = 'b' then
		open returncursor for select a.auctionid,y.itemtypename,d.description,p.minbid,p.currentmaxbid,a.auctionstatus from auction a , itemtypelist y , auctiondescription d , auctionpriceinfo p , bidtable b where a.auctionstatus='a' and a.itemtypeid=y.itemtypeid and a.auctionid=d.auctionid and a.auctionid=p.auctionid and a.auctionid=b.auctionid and ((p.currentmaxbid=-1 and p.minbid>=auxminprice and p.minbid<=auxmaxprice) or (p.currentmaxbid>=auxminprice and p.currentmaxbid <= auxmaxprice)) and (trim(itemtypeparam) is null or y.itemtypename=itemtypeparam) and b.bidvalue=p.currentmaxbid and b.userindex=auxuserindex;
		return;
	elsif listtypeparam = 'm' then
		open returncursor for select a.auctionid,y.itemtypename,d.description,p.minbid,p.currentmaxbid,a.auctionstatus from auction a,itemtypelist y,auctiondescription d , auctionpriceinfo p where a.itemtypeid= y.itemtypeid and a.auctionid=d.auctionid and a.auctionid=p.auctionid and a.selleruserindex=auxuserindex and ((p.currentmaxbid=-1 and p.minbid>=auxminprice and p.minbid<=auxmaxprice) or (p.currentmaxbid>=auxminprice and p.currentmaxbid <= auxmaxprice)) and (trim(itemtypeparam) is null or y.itemtypename=itemtypeparam) order by a.auctionstatus desc;
		return;
	elsif listtypeparam = 'w' then
		open returncursor for select a.auctionid,y.itemtypename,d.description,p.minbid,p.currentmaxbid,a.auctionstatus from auction a,itemtypelist y,auctiondescription d , auctionpriceinfo p where a.itemtypeid=y.itemtypeid and a.auctionid=d.auctionid and a.auctionid=p.auctionid and a.auctionstatus='w' and p.maxbiduserindex=auxuserindex and ((p.currentmaxbid=-1 and p.minbid>=auxminprice and p.minbid<=auxmaxprice) or (p.currentmaxbid>=auxminprice and p.currentmaxbid <= auxmaxprice)) and (trim(itemtypeparam) is null or y.itemtypename=itemtypeparam);
		return;
	end if;

exception
	when NO_DATA_FOUND then
		returncursor:=null;
		return;
end;
/

