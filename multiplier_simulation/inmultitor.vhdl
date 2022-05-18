entity inmultitor is
	--generic(zerob : bit := '0';
			--zerov : bit_vector(3 downto 0) := "0000");

	port(inmultitor_in,deinmultit_in:in bit_vector(3 downto 0);
		comanda_inmultire,clock:in bit;
		rezultat:out bit_vector(7 downto 0));	
end entity;

architecture arh_inmultitor of inmultitor is

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
		port (intrare1 :	in bit_vector(3 downto 0);
			intrare2 :		in bit_vector(3 downto 0);
			adresa :		in bit;
			iesire :		out bit_vector(3 downto 0));
	end component;

	component poarta_xor is
		port(intrare1 :	in bit;
			intrare2 :	in bit;
			iesire :	out bit);
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
		port(intrare : in bit_vector(3 downto 0);
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

--command signals
	signal initializare: 	bit;
	signal incarcare:		bit;
	signal deplasare:		bit;
	signal ultim:			bit;

--link signals
	signal xor_bis : bit;
	signal bis_m2x1 : bit;
	signal m2x1_acu : bit;
	signal and_m2x4 : bit;

	signal sum_acu : bit_vector(3 downto 0);
	signal m2x4_sum : bit_vector(3 downto 0);

--auxiliar signals
	signal zerob : bit := '0';
	signal not_ultim : bit := '1';
	signal incarcare_acu : bit := '0';
	signal clock_bis : bit := '0';

	signal zerov : bit_vector(3 downto 0) := "0000";
	signal interf_m2x4 : bit_vector(3 downto 0);
	signal interf_dei : bit_vector(3 downto 0);
	signal interf_inm : bit_vector(3 downto 0);
	signal interf_acu : bit_vector(3 downto 0);

begin

	reg_acumulator : reg_inc_par_depl_dr port map(
		intrare => sum_acu ,
		incarcare => incarcare_acu ,
		deplasare => deplasare ,
		bit_carry => m2x1_acu ,
		iesire => interf_acu);

	reg_inmultitor : reg_inc_par_depl_dr port map(
		intrare => inmultitor_in ,
		incarcare => initializare ,
		deplasare => deplasare ,
		bit_carry => interf_acu(0) ,
		iesire => interf_inm);

	reg_deinmultit : reg_inc_par port map(
		intrare => deinmultit_in ,
		incarcare => initializare ,
		iesire => interf_dei);

	sumator : sum port map(
		intrare1 => interf_acu ,
		intrare2 => m2x4_sum ,
		iesire => sum_acu);

	m2x1 : mux2x1 port map(
		intrare1 => bis_m2x1 ,
		intrare2 => zerob ,
		adresa => not_ultim ,
		iesire => m2x1_acu);

	m2x4 : mux2x4 port map(
		intrare1 => zerov ,
		intrare2(3) => zerob ,
		intrare2(2 downto 0) => interf_dei(2 downto 0) ,
		adresa => and_m2x4 ,
		iesire => m2x4_sum);

	pand : poarta_and port map(
		intrare1 => not_ultim ,
		intrare2 => interf_inm(0) ,
		iesire => and_m2x4);

	bistd : bistabil_d port map(
		data_intrare => xor_bis ,
		clock => clock_bis ,
		data_iesire => bis_m2x1);

	pxor  : poarta_xor port map(
		intrare1 => interf_inm(0) ,
		intrare2 => interf_dei(3) ,
		iesire => xor_bis);

--initialization at startup
	--initializare 	<= '0';
	--incarcare 		<= '0';
	--deplasare		<= '0';
	--ultim			<= '0';
	--not_ultim		<= '1';

-- flip-flop and acumulator reg
-- must be commanded to load on both initializare and incarcare
-- realised correctly through this process
process(initializare , incarcare , clock)
begin
	if initializare'event and initializare = '1' then
		incarcare_acu <= '1';
		clock_bis <= '1';
	end if;
	if incarcare'event then
		incarcare_acu <= incarcare;
		clock_bis <= incarcare;
	end if;
	if clock'event and clock = '1' and initializare = '1' then
		incarcare_acu <= '0';
		clock_bis <= '0';
	end if;
end process;

process(clock)
	variable stare:integer:=0;
begin

	case stare is
	when 0=>
		if clock = '0' then
			if comanda_inmultire = '1' then
				stare:=1; -- begin multiply on falling edge
				initializare <= '1';
			end if;
		end if;

		if clock = '1' then
			-- do nothing
		end if;

	when 1=>
		if clock = '0' then
			initializare 	<= '0';
			incarcare 		<= '1';

			stare := 2;
		end if;

		if clock = '1' then
			--do nothing
		end if;

	when 2=>
		if clock = '0' then
			incarcare <= '0';
			deplasare <= '1';

			stare := 3;
		end if;

		if clock = '1' then
			--do nothing
		end if;

	when 3=>
		if clock = '0' then
			incarcare <= '1';
			deplasare <= '0';

			stare := 4;
		end if;

		if clock = '1' then
			--do nothing
		end if;
	when 4=>
		if clock = '0' then
			incarcare <= '0';
			deplasare <= '1';

			stare := 5;
		end if;

		if clock = '1' then
			--do nothing
		end if;

	when 5=>
		if clock = '0' then
			incarcare <= '1';
			deplasare <= '0';

			stare := 6;
		end if;

		if clock = '1' then
			--do nothing
		end if;

	when 6=>
		if clock = '0' then
			incarcare <= '0';
			deplasare <= '1';

			stare := 7;
		end if;

		if clock = '1' then
			-- do nothing
		end if;

	when 7=>
		if clock = '0' then
			incarcare 	<= '1';
			deplasare 	<= '0';
			ultim		<= '1';
			not_ultim	<= '0';

			stare := 8;
		end if;

		if clock = '1' then
			-- do nothing
		end if;

	when 8=>
		if clock = '0' then
			incarcare <= '0';
			deplasare <= '1';

			stare := 9;
		end if;

		if clock = '1' then
			-- do nothing
		end if;

	when 9=>
		if clock = '0' then
			deplasare 	<= '0';
			ultim 		<= '0';
			not_ultim	<= '1';

			rezultat(3 downto 0) <= interf_inm;
			rezultat(7 downto 4) <= interf_acu;

			stare := 0;
		end if;

		if clock = '1' then
			-- do nothing
		end if;

	when others=>
		null;
	end case;
end process;

end;
