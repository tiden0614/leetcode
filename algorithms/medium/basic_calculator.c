int operand_stack[5000];
int operator_stack[5000];
int operand_p = 0;
int operator_p = 0;
void calc() {
    if (operator_p > 0 && operator_stack[operator_p - 1] != 2) {
        int r_op = operand_stack[--operand_p];
        int l_op = operand_stack[--operand_p];
        int op = operator_stack[--operator_p];
        if (op == 0) {
            // minus
            operand_stack[operand_p++] = l_op - r_op;
        } else {
            // plus
            operand_stack[operand_p++] = l_op + r_op;
        }
    }
}
int calculate(char* s) {
    char* p;
    int last_was_num = 0;
    while (1) {
        if (*p >= '0' && *p <= '9') {
            if (last_was_num) {
                // multi-digit number
                operand_stack[operand_p - 1] = (operand_stack[operand_p - 1] * 10) + (*p - '0');
            } else {
                operand_stack[operand_p++] = *p - '0';
                last_was_num = 1;
            }
        } else if (*p == '-') {
            last_was_num = 0;
            calc();
            operator_stack[operator_p++] = 0;
        } else if (*p == '+') {
            last_was_num = 0;
            calc();
            operator_stack[operator_p++] = 1;
        } else if (*p == '(') {
            last_was_num = 0;
            operator_stack[operator_p++] = 2;
        } else if (*p == ')') {
            last_was_num = 0;
            calc();
            if (operator_stack[operator_p - 1] == 2) {
                // pop up a (
                operator_p--;
            }
        } else if (*p == '\0') {
            calc();
            break;
        }
        *p++;
    }
    return operand_stack[operand_p - 1];
}