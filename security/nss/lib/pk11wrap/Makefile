#! gmake
#
# The contents of this file are subject to the Mozilla Public
# License Version 1.1 (the "License"); you may not use this file
# except in compliance with the License. You may obtain a copy of
# the License at http://www.mozilla.org/MPL/
# 
# Software distributed under the License is distributed on an "AS
# IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
# implied. See the License for the specific language governing
# rights and limitations under the License.
# 
# The Original Code is the Netscape security libraries.
# 
# The Initial Developer of the Original Code is Netscape
# Communications Corporation.  Portions created by Netscape are 
# Copyright (C) 1994-2000 Netscape Communications Corporation.  All
# Rights Reserved.
# 
# Contributor(s):
# 
# Alternatively, the contents of this file may be used under the
# terms of the GNU General Public License Version 2 or later (the
# "GPL"), in which case the provisions of the GPL are applicable 
# instead of those above.  If you wish to allow use of your 
# version of this file only under the terms of the GPL and not to
# allow others to use your version of this file under the MPL,
# indicate your decision by deleting the provisions above and
# replace them with the notice and other provisions required by
# the GPL.  If you do not delete the provisions above, a recipient
# may use your version of this file under either the MPL or the
# GPL.
#

#######################################################################
# (1) Include initial platform-independent assignments (MANDATORY).   #
#######################################################################

include manifest.mn

#######################################################################
# (2) Include "global" configuration information. (OPTIONAL)          #
#######################################################################

include $(CORE_DEPTH)/coreconf/config.mk

#######################################################################
# (3) Include "component" configuration information. (OPTIONAL)       #
#######################################################################



#######################################################################
# (4) Include "local" platform-dependent assignments (OPTIONAL).      #
#######################################################################

-include config.mk

#######################################################################
# (5) Execute "global" rules. (OPTIONAL)                              #
#######################################################################

include $(CORE_DEPTH)/coreconf/rules.mk

#######################################################################
# (6) Execute "component" rules. (OPTIONAL)                           #
#######################################################################



#######################################################################
# (7) Execute "local" rules. (OPTIONAL).                              #
#######################################################################

export:: private_export

# On AIX 4.3, IBM xlC_r compiler (version 3.6.6) cannot compile
# pk11slot.c in 64-bit mode for unknown reasons.  A workaround is
# to compile it with optimizations turned on.  (Bugzilla bug #63815)
ifeq ($(OS_TARGET)$(OS_RELEASE),AIX4.3)
ifeq ($(USE_64),1)
ifndef BUILD_OPT
$(OBJDIR)/pk11slot.o: pk11slot.c
	@$(MAKE_OBJDIR)
	$(CC) -o $@ -c -O2 $(CFLAGS) $<
endif
endif
endif

# Bugzilla Bug 209827: disable optimization to work around what appears
# to be a VACPP optimizer bug.
ifdef XP_OS2_VACPP
$(OBJDIR)/pk11skey.obj: pk11skey.c
	@$(MAKE_OBJDIR)
	$(CC) -Fo$@ -c $(filter-out /O+, $(CFLAGS)) $(call abspath,$<)
$(OBJDIR)/pk11slot.obj: pk11slot.c
	@$(MAKE_OBJDIR)
	$(CC) -Fo$@ -c $(filter-out /O+, $(CFLAGS)) $(call abspath,$<)
endif
