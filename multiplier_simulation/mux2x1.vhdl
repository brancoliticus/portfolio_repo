entity mux2x1 is
	port(intrare1:in bit;
		intrare2:in bit;
		adresa:in bit;
		iesire:out bit);
end entity;

architecture arh_mux2x1 of mux2x1 is
begin
	process
	begin
		if adresa = '0' then
			iesire <= intrare1;
			wait on intrare1 , adresa;
		else
			iesire <= intrare2;
			wait on intrare2 , adresa;
		end if;
	end process;
end architecture;
