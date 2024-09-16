import {themes as prismThemes} from 'prism-react-renderer';
import Autumn from './src/codetheme/autumn';
import type {Config} from '@docusaurus/types';
import type * as Preset from '@docusaurus/preset-classic';
import remarkMath from 'remark-math';
import rehypeKatex from 'rehype-katex';

const config: Config = {
  title: 'Cubitron',
  tagline: 'eyoo',
  favicon: 'favicon.ico',

  // Set the production url of your site here
  url: 'https://fest004.github.io',
  // Set the /<baseUrl>/ pathname under which your site is served
  // For GitHub pages deployment, it is often '/<projectName>/'
  baseUrl: '/Cubitron/',

  // GitHub pages deployment config.
  // If you aren't using GitHub pages, you don't need these.
  organizationName: 'fest004', // Usually your GitHub org/user name.
  projectName: 'Cubitron', // Usually your repo name.
  deploymentBranch: 'pages',
  trailingSlash: false,

  onBrokenLinks: 'throw',
  onBrokenMarkdownLinks: 'warn',

  // Even if you don't use internationalization, you can use this field to set
  // useful metadata like html lang. For example, if your site is Chinese, you
  // may want to replace "en" with "zh-Hans".
  i18n: {
    defaultLocale: 'en',
    locales: ['en'],
  },

  presets: [
    [
      'classic',
      {
        docs: {
          sidebarPath: './sidebars.ts',
          remarkPlugins: [remarkMath],
          rehypePlugins: [rehypeKatex],
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            'https://github.com/fest004/Cubitron',
        },
        blog: {
          showReadingTime: true,
          remarkPlugins: [remarkMath],
          rehypePlugins: [rehypeKatex],
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            'https://github.com/fest004/Cubitron',
        },
        theme: {
          customCss: './src/css/custom.css',
        },
      } satisfies Preset.Options,
    ],
  ],
  stylesheets: [
    {
      href: 'https://cdn.jsdelivr.net/npm/katex@0.13.24/dist/katex.min.css',
      type: 'text/css',
      integrity:
        'sha384-odtC+0UGzzFL/6PNoE8rX/SPcQDXBJ+uRepguP4QkPCm2LBxH3FA3y+fKSiJ+AmM',
      crossorigin: 'anonymous',
    },
    {
        href: 'https://fonts.googleapis.com/css?family=Inter',
        type: 'text/css',
    },
    {
        href: 'https://fonts.googleapis.com/css?family=Source Serif 4',
        type: 'text/css',
    },
    {
        href: 'https://fonts.googleapis.com/css?family=Roboto Mono',
        type: 'text/css',
    },
  ],

  themeConfig: {
    // Replace with your project's social card
    colormode: {
      defaultMode:"dark"
    },
    image: 'img/cubitron.svg',
    docs:{
      sidebar:{
        hideable: true,
      },
    },
    navbar: {
      title: 'Home',
      logo: {
        alt: 'My Site Logo',
        src: 'img/cubitron.svg',
      },
      items: [
        {
          type: 'docSidebar',
          sidebarId: 'tutorialSidebar',
          position: 'left',
          label: 'Read',
        },
        {to: '/blog', label: 'Blog', position: 'left'},
        {
          href: 'https://github.com/fest004/Cubitron',
          label: 'GitHub',
          position: 'right',
        },
        {
          href: 'https://youtube.com',
          label: 'YouTube',
          position: 'right',
        },
      ],
    },
    footer: {
      style: 'dark',
      copyright: `Version 0.0.1 Copyright © ${new Date().getFullYear()} roboboys.`,
    },
    prism:{
      theme: Autumn,
    }
  } satisfies Preset.ThemeConfig,
};

export default config;
