create or replace function getpriceinfobyauctionid
(sessionnumberparam number , auctionidparam number)
return datatypes.priceinfobyauctionid
is
	retval datatypes.priceinfobyauctionid;
	aux number(20);
	aux1 number(20);	
begin
	select userindex into aux from sessionnumbertable where sessionnumberparam=sessionnumber;
	select selleruserindex into aux1 from auction where auctionid=auctionidparam;
	if aux=aux1 then
		retval.minbid:=-1;
		retval.currentmaxbid:=-1;
		return retval;
	end if;
	select minbid,currentmaxbid into retval.minbid,retval.currentmaxbid from auctionpriceinfo where auctionid=auctionidparam;
	select i.itemtypename into retval.itemtypename from itemtypelist i , auction a where a.itemtypeid=i.itemtypeid and a.auctionid=auctionidparam;
       select d.description into retval.itemdescription from auction a , auctiondescription d where a.auctionid=auctionidparam and a.auctionid=d.auctionid; 	
	return retval;
exception
	when NO_DATA_FOUND then
		retval.minbid:=-1;
		retval.currentmaxbid:=-1;
		return retval;
end;
/
