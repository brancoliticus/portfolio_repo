entity banc_test is
end entity;

architecture arh_banc_test of banc_test is

	component bistabil_d is
		port(data_intrare:	in bit;
			clock:			in bit;
			data_iesire:	out bit);
	end component;

	component mux2x1 is
		port(intrare1:	in bit;
			intrare2:	in bit;
			adresa:		in bit;
			iesire:		out bit);
	end component;

	component mux2x4 is
		port (intrare1:	in bit_vector(3 downto 0);
			intrare2:	in bit_vector(3 downto 0);
			adresa:		in bit;
			iesire:		out bit_vector(3 downto 0));
	end component;

	component poarta_xor is
		port(intrare1:	in bit;
			intrare2:	in bit;
			iesire:		out bit);
	end component;

	component poarta_and is
		port(intrare1:	in bit;
			intrare2:	in bit;
			iesire:		out bit);
	end component;

	component reg_inc_par is
		port(intrare:	in bit_vector(3 downto 0);
			incarcare:	in bit;
			iesire: 	out bit_vector(3 downto 0));
	end component;

	component reg_inc_par_depl_dr is
		port(intrare:in bit_vector(3 downto 0);
			incarcare:	in bit;
			deplasare:	in bit;
			bit_carry:	in bit;
			iesire: 	out bit_vector(3 downto 0));
	end component;

	component sum is
		port(intrare1:	in bit_vector(3 downto 0);
			intrare2:	in bit_vector(3 downto 0);
			iesire:		out bit_vector(3 downto 0));
	end component;

	component inmultitor is
		port(
			inmultitor_in : in bit_vector(3 downto 0);
			deinmultit_in : in bit_vector(3 downto 0);
			comanda_inmultire : in bit;
			clock : in bit;
			rezultat : out bit_vector(7 downto 0));
	end component;

--for flip-flop
	--signal data_in:		bit;
	--signal clock:		bit;
	--signal data_out:	bit;

--for adder
	--signal in1:			bit_vector(3 downto 0);
	--signal in2:			bit_vector(3 downto 0);
	--signal carry:		bit;
	--signal res:			bit_vector(3 downto 0);

--for mux2x1
	--signal m1in1:			bit;
	--signal m1in2:			bit;
	--signal m1adr:			bit;
	--signal m1out:			bit;

--for mux2x4
	signal m4in1:			bit_vector(3 downto 0);
	signal m4in2:			bit_vector(3 downto 0);
	signal m4adr:			bit;
	signal m4out:			bit_vector(3 downto 0);

--for and , xor gates
	--signal in1: 			bit;
	--signal in2:			bit;
	--signal outand:		bit;
	--signal outxor:		bit;

--for register and shift register
	--signal reg_in:			bit_vector(3 downto 0);
	--signal reg_load:		bit;
	--signal reg_depl:		bit;
	--signal carry_bit:		bit;
	--signal reg_out:			bit_vector(3 downto 0);
	--signal reg_out_s:		bit_vector(3 downto 0);

	signal clock : bit;
	signal inmultitor_in : bit_vector(3 downto 0);
	signal deinmultit_in : bit_vector(3 downto 0);
	signal com_inmultire : bit;
	signal rezultat : bit_vector(7 downto 0);
	--signal zerob : bit := '0';

begin

	--bist_d:bistabil_d port map(data_in , clock , data_out);
	--data_in <= '0' , '1' after 23 ns , '0' after 43 ns , '1' after 63 ns;
	--clock <= '0' , '1' after 5 ns ,'0' after 10 ns ,'1' after 15 ns ,'0' after 20 ns ,'1' after 25 ns ,'0' after 30 ns ,'1' after 35 ns ,'0' after 40 ns ,'1' after 45 ns ,'0' after 50 ns ,'1' after 55 ns ,'0' after 60 ns ,'1' after 65 ns ,'0' after 70 ns;
	--end flip-flop

	--sum1:sum port map(in1 , in2 , carry , res);
	--end adder
	

	--m1:mux2x1 port map(m1in1 , m1in2 , m1adr , m1out);

	--m1in1 <= '0' , '1' after 20 ns , '0' after 50 ns;
	--m1in2 <= '0' , '1' after 60 ns , '0' after 80 ns;
	--m1adr <= '0' , '1' after 40 ns;
	--end mux 2x1

	--m4:mux2x4 port map(
		--intrare1 => m4in1 ,
		--intrare2(3) => zerob ,
		--intrare2(2 downto 0) => m4in2(2 downto 0) ,
		--adresa => m4adr , 
		--iesire => m4out);

	--m4in1 <= "0000" , "0001" after 10 ns , "0010" after 20 ns , "0011" after 30 ns , "0100" after 40 ns , "0101" after 50 ns;
	--m4in2 <= "1111" , "1110" after 10 ns , "1101" after 20 ns , "1100" after 30 ns , "1011" after 40 ns , "1010" after 50 ns;
	--m4adr <= '0' , '1' after 30 ns;
	--end mux 2x4

	--xorg:poarta_xor port map(in1 , in2 , outxor);
	--andg:poarta_and port map(in1 , in2 , outand);

	--in1 <= '0' , 					'1' after 20 ns , '0' after 40 ns;
	--in2 <= '0' , '1' after 10 ns , '0' after 20 ns , '1' after 30 ns;
	--end xor , and gates

	--reg:reg_inc_par port map(reg_in , reg_load , reg_out);
	--regs:reg_inc_par_depl_dr port map(reg_in , reg_load  , reg_depl , carry_bit , reg_out_s);

	--reg_in 		<= "1000" , "0010" after 80 ns;

	--reg_load <= '0';

	--reg_depl <= '0';

	--reg_load	<= '0' , '1' after 10 ns , '0' after 20 ns , '1' after 90 ns , '1' after 100 ns , '0' after 120 ns;

	--reg_depl	<= '0' , '1' after 20 ns , '0' after 30 ns , '1' after 40 ns , '0' after 50 ns , '1' after 60 ns , '0' after 70 ns , '1' after 100 ns , '0' after 110 ns;

	--carry_bit <= reg_out_s(0) after 20 ns , reg_out_s(0) after 40 ns , reg_out_s(0) after 60 ns , reg_out_s(0) after 100 ns;
	--for the registers

	inm : inmultitor port map(
		inmultitor_in => inmultitor_in ,
		deinmultit_in => deinmultit_in ,
		comanda_inmultire => com_inmultire ,
		clock => clock ,
		rezultat => rezultat);

	inmultitor_in <= "0101";
	deinmultit_in <= "1000";

	process
		variable i : integer;
	begin
		for i in 0 to 29 loop
			if i mod 2 = 0 then
				clock <= '0';
			else
				clock <= '1';
			end if;

			if i = 1 then
				com_inmultire <= '1';
			end if;
			if i = 3 then
				com_inmultire <= '0';
			end if;

			wait for 10 ns;
		end loop;

		i := 0;
	end process;

end architecture;
