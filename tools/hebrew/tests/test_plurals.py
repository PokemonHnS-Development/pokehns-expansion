import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import paths  # noqa: E402
import plurals  # noqa: E402

ITEMS_H = '''const struct ItemInfo gItemsInfo[] =
{
    [ITEM_NONE] =
    {
        .name = ITEM_NAME("????????"),
        .pocket = POCKET_ITEMS,
    },

    [ITEM_POTION] =
    {
        .name = ITEM_NAME("שיקוי"),
    #if TEXT_RTL
        .pluralName = ITEM_PLURAL_NAME("שיקויים"),
    #endif
        .pocket = POCKET_MEDICINE,
    },

    [ITEM_IRON] =
    {
        .name = ITEM_NAME("ברזל"),
        .pocket = POCKET_MEDICINE,
    },

    [ITEM_HONEY] =
    {
        .name = ITEM_NAME("דבש"),
        .pluralName = ITEM_PLURAL_NAME("דבש"),
        .pocket = POCKET_ITEMS,
    },

    [ITEM_BICYCLE] =
    {
        .name = ITEM_NAME("אופניים"),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    },

    [ITEM_TM01] = // Focus Punch
    {
        .name = ITEM_NAME("מ”מ 01"),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
    },

    [ITEM_SOUL_DEW] =
    {
        .name = ITEM_NAME("טל נשמה"),
        .importance = 1,
        .pocket = POCKET_ITEMS,
    },
};
'''


class Plurals(unittest.TestCase):
    def setUp(self):
        self.items = plurals.parse_items(ITEMS_H)

    def test_parse(self):
        self.assertEqual(self.items['ITEM_POTION']['plural'], 'שיקויים')
        self.assertIsNone(self.items['ITEM_IRON']['plural'])
        self.assertEqual(self.items['ITEM_HONEY']['plural'], 'דבש')
        self.assertEqual(self.items['ITEM_TM01']['pocket'], 'POCKET_TM_HM')

    def test_stackable(self):
        self.assertTrue(plurals.stackable(self.items['ITEM_POTION']))
        self.assertFalse(plurals.stackable(self.items['ITEM_BICYCLE']))   # key item
        self.assertFalse(plurals.stackable(self.items['ITEM_TM01']))      # מ”מ does not inflect
        self.assertFalse(plurals.stackable(self.items['ITEM_SOUL_DEW']))  # importance

    def test_complete(self):
        rows = {'ITEM_POTION': 'שיקויים', 'ITEM_IRON': 'ברזל', 'ITEM_HONEY': 'דבש'}
        self.assertEqual(plurals.check(self.items, rows), [])

    def test_item_added_later_without_a_row(self):
        probs = plurals.check(self.items, {'ITEM_POTION': 'שיקויים', 'ITEM_HONEY': 'דבש'})
        self.assertEqual(len(probs), 1)
        self.assertTrue(probs[0].startswith('MISSING ITEM_IRON'))

    def test_row_and_items_h_disagree(self):
        rows = {'ITEM_POTION': 'שיקויים', 'ITEM_IRON': 'מנות ברזל', 'ITEM_HONEY': 'דבש'}
        probs = plurals.check(self.items, rows)
        self.assertEqual(len(probs), 1)
        self.assertTrue(probs[0].startswith('MISMATCH ITEM_IRON'))


class Tree(unittest.TestCase):
    def test_every_stackable_item_has_a_hebrew_plural(self):
        items_h = os.path.join(paths.TREE, 'src', 'data', 'items.h')
        if not (os.path.exists(items_h) and os.path.exists(paths.GLOSSARY)):
            self.skipTest('no tree')
        items = plurals.parse_items(open(items_h, encoding='utf-8').read())
        self.assertEqual(plurals.check(items, plurals.load_rows(paths.GLOSSARY)), [])


if __name__ == '__main__':
    unittest.main()
