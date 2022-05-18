create or replace procedure clearjob
as
	jobnumbervar number(20);
begin
	select max(jobnumber) into jobnumbervar from loopjobnumber;
	DBMS_JOB.broken(jobnumbervar,true);
	DBMS_JOB.remove(jobnumbervar);
	commit;
end;
/
