entity reg_inc_par is
	port(intrare:in bit_vector(3 downto 0);
		incarcare:in bit;
		iesire: out bit_vector(3 downto 0));
end entity;

architecture arh_reg_inc_par of reg_inc_par is
begin
	process(incarcare)
		variable incarcare_vechi:boolean:=false;	begin
		if incarcare = '1' then
			iesire(0) <= intrare(0);
			iesire(1) <= intrare(1);
			iesire(2) <= intrare(2);
			iesire(3) <= intrare(3);
		end if;
	end process;
end architecture;
