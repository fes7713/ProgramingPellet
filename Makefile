.PHONY: clean All

All:
	@echo "----------Building project:[ CardGame2-6 - Debug ]----------"
	@cd "CardGame2-6" && "$(MAKE)" -f  "CardGame2-6.mk"
clean:
	@echo "----------Cleaning project:[ CardGame2-6 - Debug ]----------"
	@cd "CardGame2-6" && "$(MAKE)" -f  "CardGame2-6.mk" clean
