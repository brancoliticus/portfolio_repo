entity poarta_and is
	port(intrare1:in bit;
		intrare2:in bit;
		iesire: out bit);
end entity;

architecture arh_poarta_and of poarta_and is
begin
	process(intrare1 , intrare2)
	begin
		iesire <= intrare1 and intrare2;
	end process;
end architecture;
