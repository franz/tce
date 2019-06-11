-- Copyright (c) 2002-2009 Tampere University.
--
-- This file is part of TTA-Based Codesign Environment (TCE).
-- 
-- Permission is hereby granted, free of charge, to any person obtaining a
-- copy of this software and associated documentation files (the "Software"),
-- to deal in the Software without restriction, including without limitation
-- the rights to use, copy, modify, merge, publish, distribute, sublicense,
-- and/or sell copies of the Software, and to permit persons to whom the
-- Software is furnished to do so, subject to the following conditions:
-- 
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
-- 
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
-- FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
-- DEALINGS IN THE SOFTWARE.
---------------------------------------------------------------------------------
-- Title        : File for TTA
-- Project    : FlexDSP
-------------------------------------------------------------------------------
--
-- VHDL Architecture RF_lib.rf_1wr_1rd_always_1.symbol
--
-- Created:  10:55:31 11/22/05
--          by - tpitkane.tpitkane (elros)
--          at - 10:55:31 11/22/05
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2004.1 (Build 41)
---------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author   Description
-- 11/22/05      1.0     tpitkane   Created
-------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
LIBRARY work;
USE work.util.all;

ENTITY rf_1wr_1rd_always_1 IS
   GENERIC( 
      dataw   : integer := 32;
      rf_size : integer := 8
   );
   PORT( 
      clk      : IN     std_logic;
      glock    : IN     std_logic;
      r1load   : IN     std_logic;
      r1opcode : IN     std_logic_vector ( bit_width(rf_size)-1 DOWNTO 0 );
      rstx     : IN     std_logic;
      t1data   : IN     std_logic_vector (dataw-1 DOWNTO 0);
      t1load   : IN     std_logic;
      t1opcode : IN     std_logic_vector ( bit_width(rf_size)-1 DOWNTO 0 );
      r1data   : OUT    std_logic_vector (dataw-1 DOWNTO 0)
   );

-- Declarations

END rf_1wr_1rd_always_1 ;
---------------------------------------------------------------------------------
-- Title        : File for TTA
-- Project    : FlexDSP
-------------------------------------------------------------------------------
--
-- VHDL Architecture RF_lib.rf_1wr_1rd_always_1.rtl
--
-- Created:  10:55:31 11/22/05
--          by - tpitkane.tpitkane (elros)
--          at - 10:55:31 11/22/05
--
-- Generated by Mentor Graphics' HDL Designer(TM) 2004.1 (Build 41)
---------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author   Description
-- 11/22/05      1.0     tpitkane   Created
---------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
ARCHITECTURE rtl OF rf_1wr_1rd_always_1 IS

   -- Architecture declarations
   type   reg_type is array (natural range <>) of std_logic_vector(dataw-1 downto 0 );
   subtype rf_index is integer range 0 to rf_size-1;
   signal reg    : reg_type (rf_size-1 downto 0);

BEGIN

   -----------------------------------------------------------------
   input : PROCESS (clk, rstx)
   -----------------------------------------------------------------

   -- Process declarations
   variable opc : integer;


   BEGIN
      -- Asynchronous Reset
      IF (rstx = '0') THEN
         -- Reset Actions
         for idx in (reg'length-1) downto 0 loop
           reg(idx) <= (others => '0');
         end loop;  -- idx

      ELSIF (clk'EVENT AND clk = '1') THEN
         IF glock = '0' THEN
            IF t1load = '1' THEN
               opc := conv_integer(unsigned(t1opcode));
               reg(opc) <= t1data;
            END IF;
         END IF;
      END IF;
   END PROCESS input;

   -----------------------------------------------------------------
   --output : PROCESS (glock, r1load, r1opcode, reg, rstx)
   -----------------------------------------------------------------

   r1data <= reg(conv_integer(unsigned(r1opcode)));


END rtl;
