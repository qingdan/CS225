# slightly modified from the relevant post in 
# news.ycombinator.com/item?id=1375823
# this thread

dec = $(patsubst .%,%,$1)
not = $(if $1,,.)

less_eq = $(if $1,$(if $(findstring $1,$2),.,),.)
greater_eq = $(if $2,$(if $(findstring $2,$1),.,),.)
eq = $(and $(call less_eq,$1,$2),$(call greater_eq,$1,$2))
lt = $(and $(call less_eq,$1,$2),$(call not,$(call greater_eq,$1,$2)))

add = $1$2
subtract = $(if $(call not,$2),$1,$(call subtract,$(call dec,$1),$(call dec,$2)))
fibonacci = $(if $(call lt,$1,..),$1,$(call add,$(call fibonacci,$(call dec,$1)),$(call fibonacci,$(call subtract,$1,..))))

n = $(words $(subst .,. ,$1))

start = $(or $(info $(call n,$(call fibonacci,$1))),$(call start,.$1))

_ := $(call start,)
