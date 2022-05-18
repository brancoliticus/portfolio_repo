entity poarta_xor is
	port(intrare1: in bit;
		intrare2:in bit;
		iesire:out bit);
end entity;

architecture arh_poarta_xor of poarta_xor is
begin
	process(intrare1 , intrare2)
	begin
		if intrare1 = intrare2 then
			iesire<='0';
		else	
			iesire<='1';
		end if;
	end process;
end architecture;
