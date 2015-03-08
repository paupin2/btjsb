TOPDIR?=../..

ifeq ($(MINIFY),1)
	# example of minifying; replace this with whatever you use
	PREPROCESSOR:=uglifyjs -nc --ascii --lift-vars
else
	PREPROCESSOR:=cat
endif

SOURCE_DIR:=src
DEST_DIR:=dest
BUNDLER:=../btjsb
SOURCE_FILES:=$(wildcard $(SOURCE_DIR)/*.js)
DEST_FILES:=$(addprefix $(DEST_DIR)/,$(notdir $(SOURCE_FILES)))

example: $(DEST_DIR) $(DEST_FILES)

publish:
	MINIFY=1 make clean example

clean:
	rm -rf $(DEST_DIR)

$(DEST_DIR):
	mkdir -p $@

$(DEST_FILES):
	$(BUNDLER) $(addprefix $(SOURCE_DIR)/,$(notdir $@)) | $(PREPROCESSOR) > $@
	@echo "done! check example/$(DEST_DIR)/*.js"
