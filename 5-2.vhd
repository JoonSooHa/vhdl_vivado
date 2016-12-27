library ieee;
use ieee.std_logic_1164.all;

entity ander is
  port(
    a,b : in std_logic;
    result : out std_logic
  );
end ander;

architecture behavioral of ander is
begin
  process_ex : process(a,b)
    variable temp : std_logic;
  begin
    temp := a and b;
    result <= temp;
  end process process_ex;
end behavioral;
