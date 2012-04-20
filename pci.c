/*
 * This file is part of i915tool
 *
 * Copyright (c) 2008 Peter Stuge <peter@stuge.se>
 * Copyright (c) 2009 coresystems GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */
#include "video.h"

extern int verbose;
/* this all needs cleaning up but basically ... I don't like libpci. The coreboot stuff is nicer. */
struct pci_dev *
pci_get_bus_and_slot(u16 bus, u16 devfn)
{
	struct pci_dev *temp;
	struct pci_access *pacc = NULL;
	int dev = devfn >> 3;
	int func = devfn & 7;

        pacc = pci_alloc();
	if (! pacc)
		return 0;
        pci_init(pacc);
        pci_scan_bus(pacc);

	for (temp = pacc->devices; temp; temp = temp->next){
		if (temp->bus == bus &&  temp->dev == dev && temp->func == func) {
			return temp;
		}
	}
}

int
find_idlist(struct drm_device *dev, u16 vendor, u16 device)
{
	extern const struct pci_device_id pciidlist[];
	int succ = 0;
	int i;
	/* well, is it in the pciidlist */
	for(i = 0; pciidlist[i].vendor && !succ; i++){
		if (vendor == pciidlist[i].vendor && device == pciidlist[i].device){
			dev->dev_private->info = (void *)(pciidlist[i].driver_data);
			succ = 1;
		}
	}
	return succ;
}
struct pci_dev *pci_get_class(u32 class, void *unused)
{
	struct pci_access *pacc = NULL;
	struct pci_dev *temp, *ret = NULL;
        pacc = pci_alloc();
	if (! pacc)
		return ret;
        pci_init(pacc);
        pci_scan_bus(pacc);

	for (temp = pacc->devices; temp && ! ret; temp = temp->next){
		u32 linuxclass = temp->device_class << 8;
		if (verbose > 2)
			fprintf(stderr, "Check %x against dev %x\n", class, temp->device_class & 0xffff00);
		if ((linuxclass) ==  class) {
			if (verbose > 2) fprintf(stderr, "HIT\n");
			pci_fill_info(temp, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);
			/* gcc issue? Must have the return here. */
			return temp;
			ret = temp;
		}
	}
	if (verbose > 2) fprintf(stderr, "return %p\n",ret);
	return ret;
}

/* there's only going to be one device ... */
int pci_dev_find(struct drm_device *dev)
{
	int succ = 0;
	dev->pdev = pci_get_class(PCI_CLASS_DISPLAY_VGA<<8, NULL);

	if (dev->pdev)
		succ = find_idlist(dev, dev->pdev->vendor_id, dev->pdev->device_id);
	return succ;
}

/* support library for kernel style pci functions. We could do a semantic 
 * patch for it but this is easier to debug as we can fill it with prints
 * if we want. And no cpp abuse here. Keep it simple. 
 */

void
pci_read_config_byte(struct pci_dev *dev, unsigned long offset, u8 *val)
{
	*val = pci_read_byte(dev, offset);
}

void
pci_write_config_byte(struct pci_dev *dev, unsigned long offset, u8 val)
{
	pci_write_byte(dev, offset, val);
}

void
pci_read_config_word(struct pci_dev *dev, unsigned long offset, u16 *val)
{
	*val = pci_read_word(dev, offset);
}

void
pci_write_config_word(struct pci_dev *dev, unsigned long offset, u16 val)
{
	pci_write_word(dev, offset, val);
}

void
pci_read_config_dword(struct pci_dev *dev, unsigned long offset, u32 *val)
{
	*val = pci_read_long(dev, offset);
}

void
pci_write_config_dword(struct pci_dev *dev, unsigned long offset, u32 val)
{
	pci_write_long(dev, offset, val);
}

void *
pci_iomap(struct pci_dev *dev, int bar, unsigned long max)
{
	int kfd;
	u32 mmiophys = dev->base_addr[bar] & ~0xf;
	u32 mmiosize = max ? max : dev->size[bar];
	void *mmiobase;

	if (mmiophys < 0)
	  return NULL;
	kfd = open("/dev/mem", O_RDWR);
	if (kfd < 0)
		errx(1, "/dev/mem");
	mmiobase = mmap(NULL, mmiosize, PROT_WRITE|PROT_READ, MAP_SHARED, kfd, mmiophys);
	if ((void *)-1 == mmiobase)
		errx(1, "mmap");
	(void)close(kfd);
	return mmiobase;
}

