library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity coffee_machine is
  port(
    clk,reset : in std_logic;
    coin,return_in,coffee_btn,coffee_out : in std_logic;
    coin_val : in std_logic_vector(15 downto 0);
    seg_en,coffee_make,coin_return : out std_logic
  );
end coffee_machine;

architecture Behavioral of coffee_machine is
  type state_type is (idle, coin_in, ready, coffee, coin_out); 
  signal current_state, next_state : state_type;
  constant coffee_val : std_logic_vector(15 downto 0) := x"012c";    
begin
  process(current_state,coin,return_in,coffee_btn,coffee_out,coin_val)
  begin
    next_state <= current_state;
    case current_state is
      when idle => 
        if coin='1' then
          next_state <= coin_in;
        end if; 
      when coin_in => 
        if return_in='1' then
          next_state <= coin_out;
        elsif coin_val>=coffee_val then
          next_state <= ready;
        end if;
      when ready => 
        if return_in='1' or coin_val<coffee_val then
          next_state <= coin_out;
        elsif coffee_btn='1' then
          next_state <= coffee;
        end if;
      when coffee => 
        if coffee_out='1' then
          next_state <= ready;
        end if;
      when coin_out => 
        if coin_val=x"0000" then
          next_state <= idle;
        end if;
      when others => next_state <= idle;
    end case;
  end process;

  process(clk,reset)
  begin
    if reset='1' then
      current_state <= idle;
    elsif rising_edge(clk) then
      current_state <= next_state;
    end if;   
  end process;

  process(current_state)
  begin
    seg_en <= '0';
    coffee_make <= '0';
    coin_return <= '0';
    case current_state is
      when idle =>
      when coin_in => seg_en <= '1';
      when ready => seg_en <= '1';
      when coffee => seg_en <= '1';  coffee_make <= '1';
      when coin_out => seg_en <= '1';  coin_return <= '1';
    end case;        
  end process;
end Behavioral;
