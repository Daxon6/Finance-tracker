package orion.rs.demo.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import orion.rs.demo.domain.Transaction;
import orion.rs.demo.repository.TransactionRepository;
import orion.rs.demo.repository.EmployeeRepository;
import orion.rs.demo.repository.AccountRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import orion.rs.demo.service.TransactionService;

@RestController
@RequestMapping("/api/transactions")
public class TransactionController {

    private final TransactionRepository transactionRepository;
    private final EmployeeRepository employeeRepository;
    private final AccountRepository accountRepository;


    private final TransactionService transactionService;

    public TransactionController(
            TransactionRepository transactionRepository,
            EmployeeRepository employeeRepository,
            AccountRepository accountRepository, TransactionService transactionService) {
        this.transactionRepository = transactionRepository;
        this.employeeRepository = employeeRepository;
        this.accountRepository = accountRepository;
        this.transactionService = transactionService;
    }

    @PostMapping
    public ResponseEntity<?> createTransaction(@RequestBody Transaction transaction) {


        if (transaction.getReporter() == null ||
                transaction.getReporter().getId() == null ||
                !employeeRepository.existsById(transaction.getReporter().getId())) {
            return ResponseEntity.status(400).body("Employee does not exist");
        }

        if (transaction.getAccount() == null ||
                transaction.getAccount().getId() == null ||
                !accountRepository.existsById(transaction.getAccount().getId())) {
            return ResponseEntity.status(400).body("Account does not exist");
        }

        // 3. Provera obaveznih polja
        if (transaction.getDescription() == null || transaction.getDescription().trim().isEmpty()) {
            return ResponseEntity.status(400).body("Description is mandatory");
        }
        if (transaction.getDate() == null) {
            return ResponseEntity.status(400).body("Date is mandatory");
        }
        if (transaction.getAmount() == null) {
            return ResponseEntity.status(400).body("Amount is mandatory");
        }
        if (transaction.getCategory() == null || transaction.getCategory().trim().isEmpty()) {
            return ResponseEntity.status(400).body("Category is mandatory");
        }
        if (transaction.getStatus() == null) {
            return ResponseEntity.status(400).body("Status is mandatory");
        }


        try {
            Transaction saved = transactionRepository.save(transaction);
            return ResponseEntity.status(201).body(saved);
        } catch (Exception e) {
            return ResponseEntity.status(500).body("Database error");
        }
    }

    @PutMapping("/{id}")
    public ResponseEntity<?> updateTransaction(
            @PathVariable Long id,
            @RequestBody Transaction transaction) {

        try {
            transactionService.updateTrans(id,transaction);
            return ResponseEntity.status(HttpStatus.OK).build();

        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body(e.getMessage());
        }
    }
}
