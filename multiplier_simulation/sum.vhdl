entity sum is
	port(intrare1:in bit_vector(3 downto 0);
		intrare2:in bit_vector(3 downto 0);
		iesire:out bit_vector(3 downto 0));
end entity;

architecture arh_sum of sum is
begin

process(intrare1 , intrare2)
	variable carry_aux : bit := '0';
begin
	for i in 0 to 3 loop
		if intrare1(i) = '0' and intrare2(i) = '0' then
			iesire(i)<=carry_aux;
			carry_aux:='0';
		else 
			if intrare1(i) = '1' and intrare2(i) = '1' then
				iesire(i)<=carry_aux;
				carry_aux:='1';
			else
				iesire(i)<=not carry_aux;
			end if;
		end if;
	end loop;
end process;

end architecture;
