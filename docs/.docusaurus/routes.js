import React from 'react';
import ComponentCreator from '@docusaurus/ComponentCreator';

export default [
  {
    path: '/Cubitron/blog',
    component: ComponentCreator('/Cubitron/blog', '996'),
    exact: true
  },
  {
    path: '/Cubitron/blog/archive',
    component: ComponentCreator('/Cubitron/blog/archive', '265'),
    exact: true
  },
  {
    path: '/Cubitron/blog/first-blog-post',
    component: ComponentCreator('/Cubitron/blog/first-blog-post', '842'),
    exact: true
  },
  {
    path: '/Cubitron/blog/long-blog-post',
    component: ComponentCreator('/Cubitron/blog/long-blog-post', '167'),
    exact: true
  },
  {
    path: '/Cubitron/blog/mdx-blog-post',
    component: ComponentCreator('/Cubitron/blog/mdx-blog-post', '732'),
    exact: true
  },
  {
    path: '/Cubitron/blog/tags',
    component: ComponentCreator('/Cubitron/blog/tags', '7e1'),
    exact: true
  },
  {
    path: '/Cubitron/blog/tags/docusaurus',
    component: ComponentCreator('/Cubitron/blog/tags/docusaurus', '585'),
    exact: true
  },
  {
    path: '/Cubitron/blog/tags/facebook',
    component: ComponentCreator('/Cubitron/blog/tags/facebook', '906'),
    exact: true
  },
  {
    path: '/Cubitron/blog/tags/hello',
    component: ComponentCreator('/Cubitron/blog/tags/hello', '010'),
    exact: true
  },
  {
    path: '/Cubitron/blog/tags/hola',
    component: ComponentCreator('/Cubitron/blog/tags/hola', 'f94'),
    exact: true
  },
  {
    path: '/Cubitron/blog/welcome',
    component: ComponentCreator('/Cubitron/blog/welcome', '43d'),
    exact: true
  },
  {
    path: '/Cubitron/markdown-page',
    component: ComponentCreator('/Cubitron/markdown-page', '125'),
    exact: true
  },
  {
    path: '/Cubitron/docs',
    component: ComponentCreator('/Cubitron/docs', '54d'),
    routes: [
      {
        path: '/Cubitron/docs',
        component: ComponentCreator('/Cubitron/docs', 'e6c'),
        routes: [
          {
            path: '/Cubitron/docs',
            component: ComponentCreator('/Cubitron/docs', 'e4b'),
            routes: [
              {
                path: '/Cubitron/docs/category/guide',
                component: ComponentCreator('/Cubitron/docs/category/guide', '337'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/Cubitron/docs/category/reference',
                component: ComponentCreator('/Cubitron/docs/category/reference', '7e1'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/Cubitron/docs/guide/manage-docs-versions',
                component: ComponentCreator('/Cubitron/docs/guide/manage-docs-versions', '41d'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/Cubitron/docs/guide/translate-your-site',
                component: ComponentCreator('/Cubitron/docs/guide/translate-your-site', '07f'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/Cubitron/docs/intro',
                component: ComponentCreator('/Cubitron/docs/intro', 'e0c'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/Cubitron/docs/reference/yurr',
                component: ComponentCreator('/Cubitron/docs/reference/yurr', 'a04'),
                exact: true,
                sidebar: "tutorialSidebar"
              }
            ]
          }
        ]
      }
    ]
  },
  {
    path: '/Cubitron/',
    component: ComponentCreator('/Cubitron/', '198'),
    exact: true
  },
  {
    path: '*',
    component: ComponentCreator('*'),
  },
];
