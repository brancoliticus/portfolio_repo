create or replace package datatypes 
as
	type priceinfobyauctionid is record(minbid number(20),currentmaxbid number(20),itemtypename varchar2(200) , itemdescription varchar2(200));
	type auctionlistitem is record(auctionid number(20) , itemtype varchar2(200) , description varchar2(200) , minbid number(20) , currentmaxbid number(20) , active char(1));	
	type auctionlistitemcursor is ref cursor return auctionlistitem;
end;
/
