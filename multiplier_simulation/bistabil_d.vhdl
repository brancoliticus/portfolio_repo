entity bistabil_d is
	port(data_intrare:in bit;
		clock:in bit;
		data_iesire: out bit);
end entity;

architecture arh_bistabil_d of bistabil_d is
begin
	process(clock)
	begin
		if(clock = '1' and clock'event) then
			data_iesire <= data_intrare;
		end if;
	end process; 
end architecture;
