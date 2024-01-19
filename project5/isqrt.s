 # Zachary Meyers
 # UID 120279096
 # zmeyers3 
 
    .text
isqrt:

   # PROLOGUE
   subu	$sp, $sp, 8
   sw	$ra, 8($sp)
   sw	$fp, 4($sp)
   addu	$fp, $sp, 8

   # BODY
   subu $sp, $sp, 4 # create space to store n
   sw $a0, 4($sp)
   blt $a0, 2, base # go to exit if n is less than 2
   srl $a0, $a0, 2 # right shift n by two bits

   jal isqrt # recursive call

   lw $a0, 4($sp) # restore n from stack
   move $t0, $v0 # move return value into new temp variable
   sll $t0, $t0, 1 # left shift n by 1
   addu $t1, $t0, 1 # initialize large as small + 1
   mul $t2, $t1, $t1 # t2 = large squared
   
   bgt $t2, $a0, small # if large is too big
   move $v0, $t1 # otherwise, set return value to large
   j exit

   base:
      move $v0, $a0 # store n in return value
      j exit

   small:
      move $v0, $t0 # update return value to be small
      j exit

   # EPILOGUE
   exit:
    move	$sp, $fp
    lw	$ra, ($fp)
    lw	$fp, -4($sp)
    jr	$ra








