entity reg_inc_par_depl_dr is
	port(intrare:in bit_vector(3 downto 0);
		incarcare:in bit;
		deplasare:in bit;
		bit_carry:in bit;
		iesire: out bit_vector(3 downto 0));
end entity;

architecture arh_reg_inc_par_depl_dr of reg_inc_par_depl_dr is
		
	signal aux:bit_vector(2 downto 0);
begin

	process(incarcare , deplasare)
	begin
		if incarcare'event and incarcare = '1' then
			iesire(0) <= intrare(0);
		
			iesire(1) <= intrare(1);
			aux(0) <= intrare(1);
		
			iesire(2) <= intrare(2);
			aux(1) <= intrare(2);

			iesire(3) <= intrare(3);
			aux(2) <= intrare(3);
		end if; 
		if deplasare'event and deplasare = '1' then
			--if rising_edge (deplasare) then
			iesire(0) <= aux(0);
			aux(0) <= aux(1);

			iesire(1) <= aux(1);
			aux(1) <= aux(2);

			iesire(2) <= aux(2);
			aux(2) <= bit_carry;

			iesire(3) <= bit_carry;
		end if;
	end process;

end architecture;
