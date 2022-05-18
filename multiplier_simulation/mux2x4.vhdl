entity mux2x4 is
	port(intrare1:in bit_vector(3 downto 0);
		intrare2:in bit_vector(3 downto 0);
		adresa:in bit;
		iesire:out bit_vector(3 downto 0));
end entity;

architecture arh_mux2x4 of mux2x4 is
begin
--	process
--	begin--		if adresa = '0' then
--			for i in 0 to 3 loop
--				iesire(i) <= intrare1(i);
--			end loop;
--			wait on intrare1 , adresa;
--		else
--			for i in 0 to 3 loop
--				iesire(i) <= intrare2(i);
--			end loop;
--			wait on intrare2 , adresa;
--		end if;
--	end process;

	
	process(intrare1 , intrare2 , adresa)
	begin
		if adresa = '0' then
			for i in 0 to 3 loop
				iesire(i) <= intrare1(i);
			end loop;
		else
			for i in 0 to 3 loop
				iesire(i) <= intrare2(i);
			end loop;
		end if;
	end process;
end architecture;
