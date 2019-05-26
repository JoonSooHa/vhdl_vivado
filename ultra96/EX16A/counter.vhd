library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity counter is
    port(
        clk, rst, clr, en : in std_logic;
        q : out std_logic_vector(26 downto 0);
        cnt_max : out std_logic
    );
end counter;

architecture Behavioral of counter is
    signal cnt : std_logic_vector(26 downto 0);
begin
    process(clk, rst, clr, en, cnt)
    begin
        if rising_edge(clk) then
            if rst='1' or clr = '1' then
                cnt <= (others => '0');
            elsif en='1' then
                if cnt=99999999 then
                    cnt <= (others => '0');    
                else
                    cnt <= cnt + 1;
                end if;
            end if;
        end if;    
    end process;

    q <= cnt;

    process(clk, rst, cnt)
    begin
        if rising_edge(clk) then
            if rst = '1' then
                cnt_max <= '0';
            elsif cnt=99999999 then
                cnt_max <= '1';
            else
                cnt_max <= '0';
            end if;
        end if;
    end process;

    -- process(cnt)
    -- begin
    --     if cnt=99999999 then
    --         cnt_max <= '1';
    --     else
    --         cnt_max <= '0';
    --     end if;
    -- end process;
end Behavioral;
