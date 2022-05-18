create or replace procedure expireauctions
as
	auxmaxbid number(20);
begin
	DBMS_OUTPUT.put_line('expireauctions executing');
	for mycursor in 
	(select auctionid,durationminutes-(sysdate-startdate)*60*24 timeleft from auctiontimeinfo) 
	loop
		if mycursor.timeleft < 0 then
			select currentmaxbid into auxmaxbid from auctionpriceinfo where auctionid=mycursor.auctionid;
			if auxmaxbid=-1 then
				update auction set auctionstatus='f' where auctionid=mycursor.auctionid;
			else
				update auction set auctionstatus='w' where auctionid=mycursor.auctionid;
			end if;
		end if;	
	end loop;
	commit;
end;
/
