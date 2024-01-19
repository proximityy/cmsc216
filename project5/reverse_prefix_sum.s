 # Zachary Meyers
 # UID 120279096
 # zmeyers3 
 
    .text
reverse_prefix_sum:

   # PROLOGUE
   subu	$sp, $sp, 8
   sw	$ra, 8($sp)
   sw	$fp, 4($sp)
   addu	$fp, $sp, 8

   # BODY
   subu $sp, $sp, 4 # put arr pointer on stack
   sw $a0, 4($sp)
   
   lw $t0, 0($a0) # load the next value in
   li $v0, 0 # load 0 into the return value
   beq $t0, -1, exit # base case, check if next array value is -1
   addu $a0, $a0, 4 # increment a0 for recursive call

   jal reverse_prefix_sum # recursive call

   lw $a0, 4($sp) # restore $a0 array address
   lw $t0, 0($a0) # restore next array value
   addu $v0, $v0, $t0 # increment return value by current array entry
   sw $v0, 0($a0) # update array with corresponding value
   j exit

   # EPILOGUE

   exit:
    move	$sp, $fp
    lw	$ra, ($fp)
    lw	$fp, -4($sp)
    jr	$ra








