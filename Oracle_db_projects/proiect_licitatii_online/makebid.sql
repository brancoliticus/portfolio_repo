create or replace function makebid
(usersessionnumberparam number , auctionidparam number , bidvalueparam number)
return number
as
	aux number(20);
	aux1 number(20);
begin
	select userindex into aux from sessionnumbertable where sessionnumber=usersessionnumberparam;
	select selleruserindex into aux1 from auction where auctionidparam=auctionid;
	if aux=aux1 then
		return -1;
	end if;
	select currentmaxbid into aux1 from auctionpriceinfo where auctionid=auctionidparam;
	if aux1=-1 then
		select minbid into aux1 from auctionpriceinfo where auctionid=auctionidparam;
		if aux1 > bidvalueparam then
			return -1;
		end if; 
	else
		if aux1 >= bidvalueparam then
			return -1;
		end if;
	end if;
	update auctionpriceinfo set currentmaxbid=bidvalueparam,maxbiduserindex=aux where auctionid=auctionidparam;
	insert into bidtable(auctionid,userindex,biddate,bidvalue) values (auctionidparam , aux , sysdate , bidvalueparam);
	commit;
	return usersessionnumberparam;
exception
	when NO_DATA_FOUND then
		return -1;
end;
/
